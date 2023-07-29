"use strict";

// C library API
const ffi = require("ffi-napi");

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");
const fileUpload = require("express-fileupload");

app.use(fileUpload());
app.use(express.static(path.join(__dirname + "/uploads")));

// Minimization
const fs = require("fs");
const JavaScriptObfuscator = require("javascript-obfuscator");

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get("/", function (req, res) {
  res.sendFile(path.join(__dirname + "/public/index.html"));
});

// Send Style, do not change
app.get("/style.css", function (req, res) {
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname + "/public/style.css"));
});

// Send obfuscated JS, do not change
app.get("/index.js", function (req, res) {
  fs.readFile(path.join(__dirname + "/public/index.js"), "utf8", function (err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {
      compact: true,
      controlFlowFlattening: true,
    });
    res.contentType("application/javascript");
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post("/upload", function (req, res) {
  if (!req.files) {
    // return res.json({ success: false });
    // return res.status(400).send("<script></script>");
    console.log("Error no file was uploaded");
    res.send('<script>alert("No file was uploaded");</script>');
    return res.status(400);
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv("uploads/" + uploadFile.name, function (err) {
    if (err) {
      console.log("Error uploading file");
      return res.status(500).send(err);
    } else {
      if (validFile("uploads/" + uploadFile.name)) {
        console.log("Successfully uploaded file!");
        res.redirect("/");
      } else {
        fs.unlinkSync("uploads/" + uploadFile.name);
        console.log("Error file was invalid, skipped uploading");
        res.send('<script>alert("Invalid file");</script>');
        return res.status(400);
      }
    }
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get("/uploads/:name", function (req, res) {
  fs.stat("uploads/" + req.params.name, function (err, stat) {
    if (err == null) {
      res.sendFile(path.join(__dirname + "/uploads/" + req.params.name));
    } else {
      console.log("Error in file downloading route: " + err);
      res.send("");
    }
  });
});

//******************** Your code goes here ********************
app.listen(portNum);
console.log("Running app at localhost: " + portNum);

// C functions that are being used
const library = ffi.Library("./libsvgparser", {
  fileToJSON: ["string", ["string", "string"]], // return string, takes in svg and xsd
  imageToJSON: ["string", ["string", "string"]], // return string, takes in svg and xsd
  validateFile: ["bool", ["string", "string"]], // return bool, takes in svg and xsd
  getTitle: ["string", ["string", "string"]], // return string, takes in svg and xsd
  getDesc: ["string", ["string", "string"]], // return string, takes in svg and xsd
  writeTitle: ["bool", ["string", "string", "string"]], // return bool, takes in svg, xsd, and new title
  writeDesc: ["bool", ["string", "string", "string"]], // return bool, takes in svg, xsd, and new desc
  createEmptySVG: ["bool", ["string", "string"]], // return bool, takes in filename, title, and desc
  scaleShapes: ["bool", ["string", "string", "float"]], // return bool, takes in filename, component, and scale factor
  addShape: ["bool", ["string", "string", "string"]], //return bool, takes in filename, shape, and svgstring
  setAttributeWrapper: ["bool", ["string", "string", "int", "string", "string"]], // return bool, takes in filename, element type, element index, new attribute name, new attribute value
});

//get files from server
app.get("/files", (req, res) => {
  const files = fs.readdirSync("uploads");
  let images = [];
  //Populate an array with svg info from uploads dir
  files.forEach((file) => {
    if (path.extname(file) == ".svg") {
      let fileData = [];
      let result = JSON.parse(library.fileToJSON("uploads/" + file, "parser/svg.xsd"));
      // get filename
      fileData[0] = file;
      // get filesize and round as per pdf
      fileData[1] = Math.round(fs.statSync("uploads/" + file).size / 1024);
      // get numrect from json
      fileData[2] = result.numRect;
      // get numcirc from json
      fileData[3] = result.numCirc;
      // get numpaths from json
      fileData[4] = result.numPaths;
      // get numgroups from json
      fileData[5] = result.numGroups;
      // push all of those onto the empty array
      images.push(fileData);
    }
  });
  res.send({
    // send string back to client
    data: JSON.stringify(images),
  });
});

// get specific file data
app.get("/fileDetails", (req, res) => {
  //if (req.query.filename === null || req.query.filename === undefined || req.query.filename === "") {
  //res.send('<script>alert("Invalid file");</script>');
  //return res.status(400);
  //}
  let result = JSON.parse(library.imageToJSON("uploads/" + req.query.filename, "parser/svg.xsd"));
  let title = library.getTitle("uploads/" + req.query.filename, "parser/svg.xsd");
  let desc = library.getDesc("uploads/" + req.query.filename, "parser/svg.xsd");
  res.send({
    title: title,
    description: desc,
    result,
  });
});

// update title
app.get("/updateTitle", (req, res) => {
  // console.log(req.query.filename);
  // console.log(req.query.title);
  let result = library.writeTitle("uploads/" + req.query.filename, "parser/svg.xsd", req.query.title);
  res.send(result);
});

// update desc
app.get("/updateDesc", (req, res) => {
  let result = library.writeDesc("uploads/" + req.query.filename, "parser/svg.xsd", req.query.description);
  res.send(result);
});

// create empty svg
app.get("/createsvg", (req, res) => {
  if (
    fs.existsSync("uploads/" + req.query.file) ||
    req.query.title.length > 255 ||
    req.query.description.length > 255 ||
    !req.query.file.endsWith(".svg")
  ) {
    console.error("ERROR creating svg");
    res.send('<script>alert("error creating svg");</script>');
    //return res.status(400);
  } else {
    let file = req.query.file;
    let title = req.query.title;
    let description = req.query.description;
    let SVG = { title: title, descr: description };
    let d;
    d = JSON.stringify(SVG);
    //console.log(d);
    //console.log("from server " + file + " " + title + " " + description);
    let result = library.createEmptySVG("uploads/" + file, d);
    //console.log(result);
    //res.status(200).send(result);
    res.send(result);
  }
});

// scale shapes
app.get("/scale", (req, res) => {
  let result = library.scaleShapes("uploads/" + req.query.filename, req.query.shape, req.query.factor);
  //console.log("from server: " + req.query.filename + " " + req.query.shape + " " + req.query.factor);
  res.send(result);
});

app.get("/addShape", (req, res) => {
  let d;
  if (req.query.shape === "RECT") {
    let SVG = {
      x: Number(req.query.x),
      y: Number(req.query.y),
      w: Number(req.query.w),
      h: Number(req.query.h),
      units: req.query.units,
    };
    d = JSON.stringify(SVG);
  } else {
    let SVG = { cx: Number(req.query.cx), cy: Number(req.query.cy), r: Number(req.query.r), units: req.query.units };
    d = JSON.stringify(SVG);
  }
  //console.log(d);
  let result = library.addShape("uploads/" + req.query.filename, req.query.shape, d);
  res.send(result);
});

// edit attribute
app.get("/editAttr", (req, res) => {
  //console.log(req.query.filename, req.query.elemType, req.query.elementIndex, req.query.attrName, req.query.attrValue);
  let result = library.setAttributeWrapper(
    "uploads/" + req.query.filename,
    req.query.elemType,
    req.query.elementIndex,
    req.query.attrName,
    req.query.attrValue
  );
  res.send(result);
});

// make sure file is valid before uploading to server
const validFile = (filename) => {
  return library.validateFile(filename, "parser/svg.xsd");
};
