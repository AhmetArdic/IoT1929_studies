import React, {useState, useEffect} from 'react';
import {
  StyleSheet,
  Text,
  View,
  FlatList,
  Dimensions,
  TouchableOpacity,
} from 'react-native';
import {Picker} from '@react-native-picker/picker';
import Icon from 'react-native-vector-icons/FontAwesome5';
import {Input} from 'react-native-elements';
import {db} from './firebase';

const windowWidth = Dimensions.get('window').width;
const windowHeight = Dimensions.get('window').height;

export default function App() {
  const [ID, setID] = useState('');
  const [name, setName] = useState('led');
  const [page, setPage] = useState(0);
  const [devices, setDevices] = useState([]);

  useEffect(() => {
    getDataFromFirebase();
  }, [page]);

  const getDataFromFirebase = () => {
    db.ref('/').on('value', snapshot => {
      setDevices([]);
      snapshot.forEach(childSnapshot => {
        childSnapshot.forEach(childSnapshot2 => {
          setDevices(old_array => [
            ...old_array,
            {
              id: childSnapshot.key,
              name: childSnapshot2.key,
              state: childSnapshot2.val(),
            },
          ]);
        });
      });
    });
  };

  const setDataToFirebase = () => {
    db.ref(ID).set({
      [name]: 0,
    });
    setDevices([]);
  };

  const deleteItemFromFirebase = item => {
    const llDeleteItem = db.ref(item.id);
    llDeleteItem.remove();
  };

  const changeItemState = item => {
    const llChangeItem = db.ref(item.id);
    if (!item.state) {
      llChangeItem.update({
        [item.name]: 1,
      });
    } else {
      llChangeItem.update({
        [item.name]: 0,
      });
    }
  };

  const _renderItem = ({item}) => {
    return (
      <View style={styles.card}>
        <View style={{flex: 1, justifyContent: 'space-between', margin: 20}}>
          <Text style={styles.card_text}>
            <Text style={{fontWeight: 'bold', color: 'black'}}>ID: </Text>
            {item.id}
          </Text>
          <Text style={styles.card_text}>
            <Text style={{fontWeight: 'bold', color: 'black'}}>İsim: </Text>
            {item.name}
          </Text>
          <Text style={styles.card_text}>
            <Text style={{fontWeight: 'bold', color: 'black'}}>Durum: </Text>
            {item.name == 'pot' || item.name == 'gaz'
              ? item.state
              : item.state
              ? 'Açık'
              : 'Kapalı'}
          </Text>
        </View>
        <View
          style={{
            position: 'absolute',
            right: 20,
            flex: 1,
            height: windowHeight / 4.5,
            paddingVertical: 15,
            justifyContent:
              item.name == 'led' || item.name == 'relay'
                ? 'space-between'
                : 'flex-end',
          }}>
          {(item.name == 'led' || item.name == 'relay') && (
            <TouchableOpacity onPress={() => changeItemState(item)}>
              <View style={styles.change_state}>
                <Text
                  style={{
                    color: '#fff',
                    fontWeight: 'bold',
                    fontSize: 18,
                    textAlign: 'center',
                  }}>
                  Durum değiştir
                </Text>
              </View>
            </TouchableOpacity>
          )}

          <TouchableOpacity onPress={() => deleteItemFromFirebase(item)}>
            <View
              style={[
                styles.edit_button,
                {
                  backgroundColor: 'red',
                  left: item.name == 'led' || item.name == 'relay' ? 60 : 0,
                },
              ]}>
              <Icon name="times" size={24} color="#fff" />
            </View>
          </TouchableOpacity>
        </View>
      </View>
    );
  };

  return (
    <View style={styles.container}>
      {!page ? (
        devices.length == 0 ? (
          <View
            style={{
              flex: 1,
              justifyContent: 'center',
              alignItems: 'center',
            }}>
            <Text style={{fontSize: 24}}>Herhangi bir cihaz bağlı değil</Text>
          </View>
        ) : (
          <View>
            <FlatList
              style={styles.list_container}
              data={devices}
              keyExtractor={(item, index) => index.toString()}
              renderItem={_renderItem}
            />
          </View>
        )
      ) : (
        <View
          style={{
            flex: 1,
            margin: 50,
            marginBottom: 100,
            padding: 10,
            width: '100%',
            justifyContent: 'flex-end',
          }}>
          <Text style={styles.input_text}>
            Bu kısımda yazılan ID, Arduino IDE kısmında kartınıza bizim
            programımızı atarken vereceğiniz ID 'dir. Eğer ID ler eşleşmeze
            cihazınız senkronize olmayacaktır.
          </Text>

          <Input
            placeholder="Cihaz ID si"
            onChangeText={value => setID(value)}
          />

          <Picker
            selectedValue={name}
            onValueChange={(itemValue, itemIndex) => setName(itemValue)}
            style={{
              marginLeft: 10,
            }}>
            <Picker.Item label="Led" value="led" />
            <Picker.Item label="Relay" value="relay" />
            <Picker.Item label="Pot" value="pot" />
            <Picker.Item label="Gaz Sensor" value="gaz" />
          </Picker>

          <View style={[styles.float_button, {bottom: -60, right: 120}]}>
            <TouchableOpacity
              disabled={ID == '' || name == '' ? true : false}
              onPress={() => {
                setDataToFirebase();
                setPage(0);
              }}>
              <View style={[styles.button, styles.menu]}>
                <Icon name="database" size={24} color="#fff" />
              </View>
            </TouchableOpacity>
          </View>
        </View>
      )}
      <View style={[styles.float_button, {bottom: 40, right: 40}]}>
        <TouchableOpacity
          onPress={() => {
            setPage(!page);
            setDevices([]);
          }}>
          <View style={[styles.button, styles.menu]}>
            {!page ? (
              <Icon name="plus" size={24} color="#fff" />
            ) : (
              <Icon name="times" size={24} color="#fff" />
            )}
          </View>
        </TouchableOpacity>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fefe',
    alignItems: 'center',
  },
  list_container: {
    marginTop: 50,
    margin: 10,
  },
  float_button: {
    alignItems: 'center',
    position: 'absolute',
  },
  card: {
    marginBottom: 10,
    height: windowHeight / 4.5,
    width: windowWidth - 20,
    backgroundColor: '#F67280',
    borderRadius: 15,
    borderWidth: 2,
    borderColor: '#C06C84',
  },
  button: {
    //position: "absolute",
    width: 60,
    height: 60,
    borderRadius: 60 / 2,
    alignItems: 'center',
    justifyContent: 'center',
  },
  menu: {
    backgroundColor: '#f02a4b',
  },
  card_text: {
    color: 'white',
    fontSize: 20,
  },
  change_state: {
    backgroundColor: 'green',
    width: 100,
    height: 60,
    borderRadius: 15,
    alignItems: 'center',
    justifyContent: 'center',
  },
  edit_button: {
    //position: "absolute",
    backgroundColor: 'purple',
    borderRadius: 100,
    width: 40,
    height: 40,
    alignItems: 'center',
    justifyContent: 'center',
  },
  input_text: {
    backgroundColor: '#fff',
    fontSize: 18,
    padding: 20,
    marginBottom: 20,
    textAlign: 'center',
    borderWidth: 1,
  },
});
