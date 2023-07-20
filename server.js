const express = require("express");
const bodyParser = require("body-parser");
const https = require("https");
require('dotenv').config();
const app = express();

app.set("view engine", "ejs");
app.use(bodyParser.urlencoded({extended: true}));
app.use(express.static("public"));

setTimeout(function(){

app.get("/", function(req, res) {
  let channelNo = process.env.CHANNELNUMBER;
  let url = "https://api.thingspeak.com/channels/"+channelNo+"/feeds.json?results=2";
  
  https.get(url, function(response) {
    console.log(response.statusCode);
  
    response.on("data", function(data) {
      //console.log(JSON.parse(data));
      const weatherData = JSON.parse(data);
      const temp = weatherData.feeds[1].field1;
      const atm = weatherData.feeds[1].field4;
      const hum = weatherData.feeds[1].field2;
      const ligh = weatherData.feeds[1].field3;
      res.render("display_index", {tempvar: temp, atmvar: atm, humvar: hum, lightvar: ligh});

      console.log(temp); console.log(atm); console.log(hum); console.log(ligh);
    });
  });
});

}, 3000);

app.listen(3000, function() {
  console.log("Server running!");
});
