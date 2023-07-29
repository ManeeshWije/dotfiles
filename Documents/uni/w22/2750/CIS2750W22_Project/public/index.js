// Put all onload AJAX calls here, and event listeners
jQuery(document).ready(function () {
  $("#svg-select")[0].selectedIndex = 0;
  $("#shape-select")[0].selectedIndex = 0;
  $("#edit-attr-shape")[0].selectedIndex = 0;
  $("#add-shape-file")[0].selectedIndex = 0;
  $("#add-shape-component")[0].selectedIndex = 0;
  $("#scale-dropdown")[0].selectedIndex = 0;

  // On page-load AJAX Example
  jQuery.ajax({
    type: "get", //Request type
    dataType: "json", //Data type - we will use JSON for almost everything
    url: "/files", //The server endpoint we are connecting to
    //async: false,
    data: {},
    success: function (data) {
      getFiles(data);
      console.log("Successfully fetched files from server!");
      console.log(data);
    },
    fail: function (error) {
      // Non-200 return, do something with error
      alert(new Error("Could not load files." + error));
      getFiles(null);
      console.log("Error fetching files from server!");
      console.log(error);
    },
  });
  // stuff for creating an svg
  $("#svg-form").submit((e) => {
    e.preventDefault();
    let file = $("#svg-name").val();
    if (file.substring(file.length - 4) === ".svg") {
      alert(new Error("remove .svg extension"));
      return;
    } else {
      file = $("#svg-name").val() + ".svg";
    }
    let title = $("#svg-title").val();
    let description = $("#svg-desc").val();
    console.log("from client" + file + " " + title + " " + description);
    $.ajax({
      type: "get",
      dataType: "json",
      url: "/createsvg",
      //async: false,
      data: {
        file: file,
        title: title,
        description: description,
      },
      success: function (data) {
        //console.log(data);
        console.log("Successfully added file: " + file);
        alert("Successfully added file: " + file);
        location.reload();
      },
      fail: function (error) {
        alert(new Error("Error adding file"));
        console.log(error);
      },
    });
  });
  // stuff for scaling shapes
  $("#scale-shape").submit((e) => {
    e.preventDefault();
    let filename = $("#scale-dropdown").val();
    let shape = $("#shape-to-scale").val();
    let factor = $("#scale-factor").val();
    console.log("from client " + filename + " " + shape + " " + factor);
    if (filename === null) {
      alert(new Error("Invalid filename selected"));
      return;
    }
    $.ajax({
      type: "get",
      dataType: "json",
      url: "/scale",
      //async: false,
      data: {
        filename: filename,
        shape: shape,
        factor: factor,
      },
      success: function (data) {
        //console.log(data);
        console.log("Successfully scaled shape");
        alert("Successfully scaled shape");
        location.reload();
      },
      fail: function (error) {
        alert(new Error("Error scaling shape"));
        console.log(error);
      },
    });
  });
  $("#add-shape-component").val("Rectangle").change();
  // adding a rectangle
  $("#add-shape-rect").submit((e) => {
    e.preventDefault();
    let filename = $("#add-shape-file").val();
    let shape = "RECT";
    let x = $("#x").val();
    let y = $("#y").val();
    let w = $("#w").val();
    let h = $("#h").val();
    let units = $("#rect-units").val();
    console.log(filename, x, y, w, h, units);
    if (filename === null) {
      alert(new Error("Invalid filename selected"));
      return;
    }
    $.ajax({
      type: "get",
      dataType: "json",
      url: "/addShape",
      async: false,
      data: {
        filename: filename,
        shape: shape,
        x: x,
        y: y,
        w: w,
        h: h,
        units: units,
      },
      success: function (data) {
        //console.log(data);
        console.log("Successfully added rectangle");
        alert("Successfully added rectangle");
        location.reload();
      },
      fail: function (error) {
        alert(new Error("Error adding rectangle"));
        console.log(error);
      },
    });
  });
  // for circles
  $("#add-shape-circ").submit((e) => {
    e.preventDefault();
    let filename = $("#add-shape-file").val();
    let shape = "CIRC";
    let cx = $("#cx").val();
    let cy = $("#cy").val();
    let r = $("#r").val();
    let units = $("#circ-units").val();
    console.log(filename, cx, cy, r, units);
    if (filename === null) {
      alert(new Error("Invalid filename selected"));
      return;
    }
    $.ajax({
      type: "get",
      dataType: "json",
      url: "/addShape",
      async: false,
      data: {
        filename: filename,
        shape: shape,
        cx: cx,
        cy: cy,
        r: r,
        units: units,
      },
      success: function (data) {
        //console.log(data);
        console.log("Successfully added circle");
        alert("Successfully added circle");
        location.reload();
      },
      fail: function (error) {
        alert(new Error("Error adding circle"));
        console.log(error);
      },
    });
  });
  // for editing an attribute
  $("#attr-edit").submit((e) => {
    e.preventDefault();
    let filename = $("#svg-select").val();
    let elemType = $("#edit-attr-shape").val();
    let elementIndex = $("#attr-index").val() - 1;
    let attrName = $("#attr-name").val();
    let attrValue = $("#attr-value").val();
    console.log(filename, elemType, elementIndex, attrName, attrValue);
    if (elemType === null || filename === null || elemType === "") {
      alert(new Error("Invalid shape or file not properly selected"));
      return;
    }
    $.ajax({
      type: "get",
      dataType: "json",
      url: "/editAttr",
      async: false,
      data: {
        filename: filename,
        elemType: elemType,
        elementIndex: elementIndex,
        attrName: attrName,
        attrValue: attrValue,
      },
      success: function (data) {
        //console.log(data);
        console.log("Successfully saved attribute");
        alert("Successfully saved attribute");
        location.reload();
      },
      fail: function (error) {
        alert(new Error("Error saving attribute"));
        console.log(error);
      },
    });
  });
});

const checkShape = () => {
  if ($("#add-shape-component").val() === "Rectangle") {
    $("#add-shape-circ").hide();
    $("#add-shape-rect").show();
    return "Rectangle";
  } else {
    $("#add-shape-rect").hide();
    $("#add-shape-circ").show();
    return "Circle";
  }
};

const getFiles = (res) => {
  const table = $("#file-log-table");

  // Show error if files could not be loaded
  if (res === null) {
    table.append('<tr><th colspan="7">Error loading files</th></tr>');
    return;
  }

  // array of strings
  const images = JSON.parse(res.data);

  if (images.length === 0) {
    table.append('<th colspan="7">No files</th>');
  } else {
    // add table titles
    table.append(
      "<th>Image<br/>(click to download)</th>" +
        "<th>File name<br/>(click to download)</th>" +
        "<th>File size</th>" +
        "<th>Number of rectangles</th>" +
        "<th>Number of circles</th>" +
        "<th>Number of paths</th>" +
        "<th>Number of groups</th>"
    );

    // now add all info dynamically
    for (let i = 0; i < images.length; i++) {
      table.append(
        "<tr>" +
          '<td class="image-thumb"> <a href="' +
          images[i][0] +
          `"download="` +
          images[i][0] +
          '">' +
          '<img src="' +
          images[i][0] +
          `"</` +
          "</a>" +
          "</td>" +
          '<td class="file-name"><a href="' +
          images[i][0] +
          `"download="` +
          images[i][0] +
          '">' +
          images[i][0] +
          "</td>" +
          '<td class="file-size">' +
          images[i][1] +
          "KB" +
          "</td>" +
          '<td class="numRects">' +
          images[i][2] +
          "</td>" +
          '<td class="numCircles">' +
          images[i][3] +
          "</td>" +
          '<td class="numPaths">' +
          images[i][4] +
          "</td>" +
          '<td class="numGroups">' +
          images[i][5] +
          "</td>" +
          "</tr>"
      );

      //Add SVGs to dropdown menus
      $("#svg-select").append(
        '<option value="' + images[i][0] + '" class="image-option ' + images[i][0] + '">' + images[i][0] + "</option>"
      );
      $("#scale-dropdown").append(
        '<option value="' + images[i][0] + '" class="image-option ' + images[i][0] + '">' + images[i][0] + "</option>"
      );
      $("#add-shape-file").append(
        '<option value="' + images[i][0] + '" class="image-option ' + images[i][0] + '">' + images[i][0] + "</option>"
      );
    }
  }
};
const getDetails = (img) => {
  let imageJSON;
  const table = $("#svg-view-table");
  const attrTable = $("#attr-table");
  const attrDropdown = $();
  $("#svg-select").val(img);
  // console.log("im here");
  $.ajax({
    type: "get",
    dataType: "json",
    url: "/fileDetails",
    async: false,
    data: {
      filename: img,
    },
    success: function (data) {
      console.log("Successfully fetched file information!");
      console.log(data);
      imageJSON = data;
    },
    fail: function (error) {
      console.log("Error in fetching file information!");
      alert(new Error("Could not load data for file. " + error));
    },
  });
  //console.log(img);
  // quick check for selected value
  if (
    imageJSON === undefined ||
    imageJSON === null ||
    imageJSON === "" ||
    $("#svg-select").val() === "Select an image" ||
    imageJSON === "Select an image"
  ) {
    console.log("Error, json is undefined or is an empty string!");
    alert("Error, json is undefined or is an empty string!");
  }
  // we clear the table from anything and start adding all the elements
  //console.log(imageJSON);
  table.empty();
  attrTable.empty();
  $("#shape-select").empty();
  $("#edit-attr-shape").empty();
  $("#shape-select").append(`<option id="bruh" selected value>Select Shape</option>`);
  $("#edit-attr-shape").append(`<option id="bruh" selected value>Select Shape</option>`);
  table.append(
    '<tr><td colspan="6" rowspan="2"><img id="image-view" src="' +
      img +
      `"/></td></tr>"` +
      "<tr></tr>" +
      '<tr><td colspan="2" class="details"><b>Title</b></td><td colspan="4" class="details"><b>Description</b></td></tr>' +
      '<tr><td colspan="2"><textarea class="image-title"' +
      img +
      '" maxlength="255">' +
      imageJSON.title +
      '</textarea><button onclick="writeTitle()">Save</button></td>' +
      '<td colspan="4"><textarea class="image-description"' +
      img +
      '" maxlength="255">' +
      imageJSON.description +
      '</textarea><button onclick="writeDesc()">Save</button></td></tr>' +
      '<tr><td class="details"><b>Component</b></td><td colspan="4" class="details"><b>Summary</b></td><td class="other-attributes"><b>Other attributes</b></td></tr>'
  );
  // now add details for each shape/attr by looping thru each
  imageJSON.result.rectangles.forEach((rect, index) => {
    table.append(
      "<tr><td>Rectangle " +
        (index += 1) +
        '</td><td colspan="4">Top left: x=' +
        rect.x +
        rect.units +
        ", y=" +
        rect.y +
        rect.units +
        "<br>" +
        "Width: " +
        rect.w +
        rect.units +
        " Height: " +
        rect.h +
        rect.units +
        '</td><td class="other-attributes">' +
        rect.numAttr +
        "</td></tr>"
    );
  });
  // add to shape dropdown list
  if (imageJSON.result.rectangles.length > 0) {
    $("#shape-select").append(`<option value="Rectangles">Rectangles</option>`);
    $("#edit-attr-shape").append(`<option value="Rectangles">Rectangles</option>`);
  }
  // do circles
  imageJSON.result.circles.forEach((circ, index) => {
    table.append(
      "<tr><td>Circle " +
        (index += 1) +
        '</td><td colspan="4">Center: cx=' +
        circ.cx +
        circ.units +
        ", cy=" +
        circ.cy +
        circ.units +
        "<br>" +
        "Radius: " +
        circ.r +
        circ.units +
        '</td><td class="other-attributes">' +
        circ.numAttr +
        "</td></tr>"
    );
  });
  // add to shape dropdown list
  if (imageJSON.result.circles.length > 0) {
    $("#shape-select").append(`<option value="Circles">Circles</option>`);
    $("#edit-attr-shape").append(`<option value="Circles">Circles</option>`);
  }
  // do paths
  imageJSON.result.paths.forEach((path, index) => {
    table.append(
      "<tr><td>Path " +
        (index += 1) +
        "</td><td colspan='4'>Data: " +
        path.d +
        '</td><td class="other-attributes">' +
        path.numAttr +
        `<td></tr>`
    );
  });
  // add to shape dropdown list
  if (imageJSON.result.paths.length > 0) {
    $("#shape-select").append(`<option value="Paths">Paths</option>`);
    $("#edit-attr-shape").append(`<option value="Paths">Paths</option>`);
  }
  // do groups
  imageJSON.result.groups.forEach((group, index) => {
    table.append(
      "<tr><td>Group " +
        (index += 1) +
        '</td><td colspan="4">Number of children: ' +
        group.children +
        '</td><td class="other-attributes">' +
        group.numAttr +
        "</td></tr>"
    );
  });
  // add to shape dropdown list
  if (imageJSON.result.groups.length > 0) {
    $("#shape-select").append(`<option value="Groups">Groups</option>`);
    $("#edit-attr-shape").append(`<option value="Groups">Groups</option>`);
  }
  $("#edit-attr-shape").append(`<option value="SVG Image">SVG Image</option>`);
};

const showAttr = () => {
  // get the filename
  const img = $("#svg-select").val();
  //console.log(img);

  let allShapes;
  $.ajax({
    type: "get",
    dataType: "json",
    url: "/fileDetails",
    async: false,
    data: {
      filename: img,
    },
    success: function (data) {
      console.log("Successfully fetched shapes!");
      // console.log(data);
      // now we have all the shapes
      allShapes = data;
    },
    fail: function (error) {
      console.log("Error in fetching shapes!");
      alert(new Error("Could not get shapes " + error));
    },
  });
  const table = $("#attr-table");
  table.empty();
  if ($("#shape-select").val() === "Rectangles") {
    //console.log("selected rectangles");
    table.empty();
    allShapes.result.rectangles.forEach((rect, index) => {
      table.append(
        "<tr><th>Rectangle " +
          (index += 1) +
          `</th></tr><tr><td>x:<span> ` +
          rect.x +
          `</span></td></tr><tr><td>y:<span> ` +
          rect.y +
          `</span></td></tr><tr><td>width:<span> ` +
          rect.w +
          `</span></td></tr></tr><td>height:<span> ` +
          rect.h +
          `</span></td></tr><tr><td>units:<span> ` +
          rect.units +
          `</span></td></tr>`
      );
      rect.otherAttrs.forEach((a) => {
        table.append(`<tr><td><b>Name</b></td><td><b>Value</b></td></tr>`);
        table.append(`<tr><td><p> ` + a.name + `</p></td><td><p> ` + a.value + `</p></td></tr>`);
      });
    });
  }
  if ($("#shape-select").val() === "Circles") {
    //console.log("selected circles");
    table.empty();
    allShapes.result.circles.forEach((circ, index) => {
      table.append(
        "<tr><th>Circle " +
          (index += 1) +
          `</th></tr><tr><td>cx:<span> ` +
          circ.cx +
          `</span></td></tr><tr><td>cy:<span> ` +
          circ.cy +
          `</span></td></tr><tr><td>r:<span> ` +
          circ.r +
          `</span></td></tr><tr><td>units:<span> ` +
          circ.units +
          `</span></td></tr>`
      );
      circ.otherAttrs.forEach((a) => {
        table.append(`<tr><td><b>Name</b></td><td><b>Value</b></td></tr>`);
        table.append(`<tr><td><p> ` + a.name + `</p></td><td><p> ` + a.value + `</p></td></tr>`);
      });
    });
  }
  if ($("#shape-select").val() === "Paths") {
    //console.log("selected paths");
    table.empty();
    allShapes.result.paths.forEach((path, index) => {
      table.append("<tr><th>Path " + (index += 1) + `</th></tr><td>d:</br><span> ` + path.d + `</span></td>`);
      path.otherAttrs.forEach((a) => {
        table.append(`<tr><td><b>Name</b></td><td><b>Value</b></td></tr>`);
        table.append(`<tr><td><p> ` + a.name + `</p></td><td><p> ` + a.value + `</p></td></tr>`);
      });
    });
  }
  if ($("#shape-select").val() === "Groups") {
    //console.log("selected groups");
    table.empty();
    allShapes.result.groups.forEach((group, index) => {
      table.append("<tr><th>Group " + (index += 1) + `</th></tr>`);
      group.otherAttrs.forEach((a) => {
        table.append(`<tr><td><b>Name</b></td><td><b>Value</b></td></tr>`);
        table.append(`<tr><td><p> ` + a.name + `</p></td><td><p> ` + a.value + `</p></td></tr>`);
      });
    });
  }
};

// function to update the title on a selected svg
const writeTitle = () => {
  const title = $(".image-title").val();
  const image = $("#image-view").attr("src");
  $.ajax({
    type: "get",
    dataType: "json",
    url: "/updateTitle",
    async: false,
    data: {
      filename: image,
      title: title,
    },
    success: function (data) {
      console.log("Successfully updated title!");
      // console.log(data);
      alert("Successfully updated title!");
      location.reload();
    },
    fail: function (error) {
      console.log("Error in updating title!");
      alert(new Error("Could not save data for file. " + error));
    },
  });
};

// function to save new description for selected svg
const writeDesc = () => {
  const desc = $(".image-description").val();
  const image = $("#image-view").attr("src");
  $.ajax({
    type: "get",
    dataType: "json",
    url: "/updateDesc",
    async: false,
    data: {
      filename: image,
      description: desc,
    },
    success: function (data) {
      console.log("Successfully updated description!");
      alert("Successfully updated description!");
      location.reload();
    },
    fail: function (error) {
      console.log("Error in updating description!");
      alert(new Error("Could not save data for file. " + error));
    },
  });
};
