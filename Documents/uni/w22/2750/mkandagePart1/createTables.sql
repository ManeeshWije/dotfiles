-- create file table
CREATE TABLE FILE (
  svg_id INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
  file_name VARCHAR(60) NOT NULL,
  file_title VARCHAR(256), 
  file_description VARCHAR(256),
  creation_time DATETIME NOT NULL,
  file_size INT NOT NULL
);
\! echo Created FILE table

-- create modification table
CREATE TABLE MODIFICATION (
  mod_id INT AUTO_INCREMENT PRIMARY KEY,
  mod_type VARCHAR(256) NOT NULL,
  mod_summary VARCHAR(256) NOT NULL,
  mod_date DATETIME NOT NULL,
  svg_id INT NOT NULL,
  FOREIGN KEY (svg_id) REFERENCES FILE(svg_id) ON DELETE CASCADE
);
\! echo Created MODIFICATION table

-- create download table
CREATE TABLE DOWNLOAD (
  download_id INT AUTO_INCREMENT PRIMARY KEY,
  d_time DATETIME NOT NULL,
  d_hostname VARCHAR(256) NOT NULL,
  svg_id INT NOT NULL,
  FOREIGN KEY (svg_id) REFERENCES FILE(svg_id) ON DELETE CASCADE
);
\! echo created DOWNLOAD table
