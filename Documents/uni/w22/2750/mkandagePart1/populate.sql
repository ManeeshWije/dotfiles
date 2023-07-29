-- insert dummy data into file table
INSERT INTO FILE (file_name, file_title, file_description, creation_time, file_size) VALUES
("rects.svg", "rectangle", "this is a rectangle", "2022-03-20 02:30:00", 1), 
("Emoji_poo.svg", "poop", "this is a poop", "2022-03-21 01:00:00", 5),
("quad01.svg", "quadratic", "this is a quadratic", "2022-03-22 19:23:25", 3),
("vest.svg", "vest", "this is a vest", "2022-03-23 03:15:07", 2),
("hen_and_chicks.svg", "hen and chick", "this is hens and chicks", "2022-03-24 12:00:00", 9),
("rects_gg.svg", "rectangle group", "this is a rectangle with nested groups", "2022-03-25 14:37:40", 2),
("Emoji_grinning.svg", "smile", "this is an emoji smiling", "2022-03-26 18:00:00", 5),
("satisfaction.svg", "satisfaction", "this is a satisfying", "2022-03-27 19:40:25", 9),
("rects_with_units.svg", "rectangles with units", "rectangles using unit cm", "2022-03-28 22:15:07", 2),
("beer.svg", "beer mug", "this is a beer mug picture", CURRENT_TIMESTAMP, 10);
\! echo Inserted data into FILE table

-- insert dummy data into modification table
INSERT INTO MODIFICATION (mod_type, mod_summary, mod_date, svg_id) VALUES 
("add attribute", "adding fill", "2022-03-20 20:20:20", 1),
("change attribute", "changing fill", "2022-03-21 18:00:59", 2),
("add circle", "new circle top left", "2022-03-22 15:00:00", 3),
("add rectangle", "new rectangle top left", "2022-03-23 23:50:30", 4),
("add path", 'new path', "2022-03-24 05:42:04", 5),
("add group", "new group", "2022-03-25 10:30:34", 6),
("change attribute", "changing stroke-width", "2022-03-26 12:24:25", 7),
("add attribute", "adding fill", "2022-03-27 13:53:24", 8),
("change rectange", "changing width", "2022-03-28 14:10:10", 9),
("change circle", "changing radius", CURRENT_TIMESTAMP, 10);
\! echo Inserted data into MODIFICATION table

-- insert dummy data into download table
INSERT INTO DOWNLOAD (d_time, d_hostname, svg_id) VALUES 
("2022-03-20 19:20:30", "hostname1", 1),
("2022-03-21 12:59:59", "hostname2", 2),
("2022-03-22 13:34:30", "hostname3", 3),
("2022-03-23 15:23:32", "hostname4", 4),
("2022-03-24 17:37:32", "hostname5", 5),
("2022-03-25 18:20:21", "hostname6", 6),
("2022-03-26 21:23:21", "hostname7", 7),
("2022-03-27 22:30:59", "hostname8", 8),
("2022-03-28 23:21:45", "hostname9", 9),
(CURRENT_TIMESTAMP, "hostname10", 10);
\! echo Inserted data into DOWNLOAD table
