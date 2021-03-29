import * as firebase from "firebase";
import "firebase/database";

const firebaseConfig = {
  /*
	YOUR_API_CONFIG
  */
};

let app;
if (firebase.apps.length === 0) {
  //app bir kere initialize edildikten sonra daha etmesin diye
  app = firebase.initializeApp(firebaseConfig);
} else {
  app = firebase.app();
}

const db = firebase.database();

export { db };
