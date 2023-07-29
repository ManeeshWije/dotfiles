-- Display all columns from all files, sorted by file name 
SELECT * 
  FROM FILE 
  ORDER BY file_name;
\! echo Done query1

-- Display all columns of all modifications, sorted by modification date (most recent first)
SELECT * 
  FROM MODIFICATION 
  ORDER BY mod_date 
  DESC;
\! echo Done query2

-- Display names, sizes, and modification dates of all files modified between specific dates, sorted by file size
SELECT 
  file_name, file_size, mod_date 
FROM 
  FILE, MODIFICATION 
WHERE 
  FILE.svg_id = MODIFICATION.svg_id AND mod_date BETWEEN "2022-03-20 00:00:00" AND "2022-03-23 23:59:59"
  ORDER BY file_size;
\! echo Done query3

-- Display the name and download date of the most recently downloaded file
SELECT 
  file_name, d_time 
FROM 
  FILE, DOWNLOAD 
WHERE 
  FILE.svg_id = DOWNLOAD.svg_id 
  ORDER BY d_time 
  DESC LIMIT 1;
\! echo Done query4

-- Display the names, sizes, and creation dates of minimum and maximum file sizes and their respective download dates 
-- ordered by file size
SELECT 
  file_name, file_size, d_time
FROM
  FILE JOIN DOWNLOAD
  ON FILE.svg_id = DOWNLOAD.svg_id
WHERE
  FILE.file_size = (SELECT MIN(file_size) FROM FILE) OR file_size = (SELECT MAX(file_size) FROM FILE)
  ORDER BY file_size;
\! echo Done query5

-- Display the oldest modified file and its modification date
SELECT 
  file_name, mod_date
FROM
  FILE JOIN MODIFICATION
  ON FILE.svg_id = MODIFICATION.svg_id
WHERE
  MODIFICATION.mod_date = (SELECT MIN(mod_date) FROM FILE
  JOIN MODIFICATION
  ON FILE.svg_id = MODIFICATION.svg_id);
\! echo Done query6

-- Display the name, description, size, mod summary, mod type, and mod date of all files that have the word "change" 
-- in their mod type sorted by file size
SELECT 
  file_name, file_description, file_size, mod_type, mod_summary, mod_date
FROM
  FILE JOIN MODIFICATION
  ON FILE.svg_id = MODIFICATION.svg_id
WHERE
  mod_type LIKE "%change%"
  ORDER BY file_size;
\! echo Done query7

