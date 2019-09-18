(function() {

    // Set the configuration for your app
    // TODO: Replace with your project's config object
    var config = {
        apiKey: "AIzaSyAE6wF6gRyvTGpZV5Vbtj_8gxrHaHBQBK0",
        authDomain: "dummy-99011.firebaseapp.com",
        databaseURL: "https://dummy-99011.firebaseio.com",
        projectId: "dummy-99011",
        storageBucket: "dummy-99011.appspot.com",
        messagingSenderId: "1010600304984",
        appId: "1:1010600304984:web:37311d3becd5bc8203852d"
    };


    // Initilization
    firebase.initializeApp(config);
    database = firebase.database();

    // What database object to choose
    var ref = database.ref('DHT11/Temperature');

    // On incoming data, retrieve data
    ref.on('value', gotData, errData);
    let newdata = []
    // Good authentication
    function gotData(data) {
        data_write = JSON.stringify(data.val());
        
        console.log(data_write);
    }

    // Bad authentication
    function errData(err) {
        console.log("ERROR");
        console.log(err);
    }
}());