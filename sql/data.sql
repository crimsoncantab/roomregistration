INSERT INTO priv VALUES 
('f','faculty',10,true,false),
('t','tf',8,true,false),
('s','student_grp',5,false,false),
('b','building_mgr',12,true,true),
('a','admin_asst',9,true,false),
('r','sysadmin',15,true,true);

INSERT INTO pageperm VALUES
('about.php', 'About Us', '0ftsbar'),
('home.php', 'Dashboard', 'ftsbar'),
('index.php', 'Home', '0'),
('roomreq.php', 'Request Room', 'ftsbar'),
('logout.php', 'Logout', 'ftsbar')
;

INSERT INTO campus VALUES
('q','quad'),
('r','river'),
('y','harvard_yard'),
('n','north_campus');

INSERT INTO users VALUES
('11111111','1','faculty1','other','faculty1@harvard.edu','6174951111','f','y'),
('11111112','1','faculty2','other','faculty2@harvard.edu','6174951111','f','y'),
('11111113','1','faculty3','other','faculty3@harvard.edu','6174951111','f','y'),
('11111114','1','faculty4','other','faculty4@harvard.edu','6174951111','f','y'),
('11111115','1','faculty5','other','faculty5@harvard.edu','6174951111','f','q'),
('11111116','1','faculty6','other','faculty6@harvard.edu','6174951111','f','q'),
('11111117','1','faculty7','other','faculty7@harvard.edu','6174951111','f','n'),
('11111118','1','faculty8','other','faculty8@harvard.edu','6174951111','f','n'),
('11111119','1','faculty9','other','faculty9@harvard.edu','6174951111','f','n'),

('21111111','2','tf1','college','tf1@harvard.edu','6174951112','t','y'),
('21111112','2','tf2','college','tf2@harvard.edu','6174951112','t','y'),
('21111113','2','tf3','college','tf3@harvard.edu','6174951112','t','y'),
('21111114','2','tf4','college','tf4@harvard.edu','6174951112','t','y'),
('21111115','2','tf5','college','tf5@harvard.edu','6174951112','t','y'),
('21111116','2','tf6','college','tf6@harvard.edu','6174951112','t','q'),
('21111117','2','tf7','college','tf7@harvard.edu','6174951112','t','n'),
('21111118','2','tf8','college','tf8@harvard.edu','6174951112','t','n'),
('21111119','2','tf9','college','tf9@harvard.edu','6174951112','t','n'),

('31111111','3','studentgroup1','college','studentgroup1@harvard.edu','6174951113','s','y'),
('31111112','3','studentgroup2','college','studentgroup2@harvard.edu','6174951113','s','y'),
('31111113','3','studentgroup3','college','studentgroup3@harvard.edu','6174951113','s','y'),
('31111114','3','studentgroup4','college','studentgroup4@harvard.edu','6174951113','s','y'),
('31111115','3','studentgroup5','college','studentgroup5@harvard.edu','6174951113','s','q'),
('31111116','3','studentgroup6','college','studentgroup6@harvard.edu','6174951113','s','r'),
('31111117','3','studentgroup7','college','studentgroup7@harvard.edu','6174951113','s','r'),
('31111118','3','studentgroup8','college','studentgroup8@harvard.edu','6174951113','s','r'),
('31111119','3','studentgroup9','college','studentgroup9@harvard.edu','6174951113','s','r'),

('41111111','4','buildingmgr1','other','buildingmgr1@harvard.edu','6174951114','b',NULL),
('41111112','4','buildingmgr2','other','buildingmgr2@harvard.edu','6174951114','b',NULL),
('41111113','4','buildingmgr3','other','buildingmgr3@harvard.edu','6174951114','b',NULL),
('41111114','4','buildingmgr4','other','buildingmgr4@harvard.edu','6174951114','b',NULL),
('41111115','4','buildingmgr5','other','buildingmgr5@harvard.edu','6174951114','b',NULL),
('41111116','4','buildingmgr6','other','buildingmgr6@harvard.edu','6174951114','b',NULL),

('51111111','5','adminasst1','other','adminasst1@harvard.edu','6174951115','a',NULL),
('51111112','5','adminasst2','other','adminasst2@harvard.edu','6174951115','a',NULL),
('51111113','5','adminasst3','other','adminasst3@harvard.edu','6174951115','a',NULL),
('51111114','5','adminasst4','other','adminasst4@harvard.edu','6174951115','a',NULL),
('51111115','5','adminasst5','other','adminasst5@harvard.edu','6174951115','a',NULL),
('51111116','5','adminasst6','other','adminasst6@harvard.edu','6174951115','a',NULL),

('61111111','6','sysadmin1','other','sysadmin1@harvard.edu','6174951116','r',NULL),
('61111112','6','sysadmin2','other','sysadmin2@harvard.edu','6174951116','r',NULL)
;

INSERT INTO building VALUES
('MD','n','Maxwell Dworkin'),
('SV','y','Sever'),
('SC','n','Science Center'),
('PC','n','Pierce'),
('EM','y','Emerson');


INSERT INTO room VALUES
('1','MD',true,15),
('2','MD',true,150),
('3','MD',false,10),
('4','MD',true,14),
('5','MD',false,200),
('6','MD',true,13),
('7','MD',true,12),
('8','MD',false,10),
('9','MD',true,130),
('10','MD',false,120),
('11','MD',true,10),
('12','MD',false,15),
('13','MD',true,15),
('14','MD',false,150),
('15','MD',false,25),
('16','MD',false,24),
('17','MD',false,20),

('1','SV',true,15),
('2','SV',true,150),
('3','SV',false,10),
('4','SV',true,14),
('5','SV',false,200),
('6','SV',true,13),
('7','SV',true,12),
('8','SV',false,10),
('9','SV',true,130),
('10','SV',false,120),
('11','SV',true,10),
('12','SV',false,15),
('13','SV',true,15),
('14','SV',false,150),
('15','SV',false,25),
('16','SV',false,24),
('17','SV',false,20),

('1','SC',true,15),
('2','SC',true,300),
('3','SC',false,10),
('4','SC',true,24),
('5','SC',false,200),
('6','SC',true,13),
('7','SC',true,20),
('8','SC',false,10),
('9','SC',true,130),
('10','SC',false,120),
('11','SC',true,10),
('12','SC',false,15),
('13','SC',true,15),
('14','SC',false,50),
('15','SC',false,25),
('16','SC',false,25),
('17','SC',false,20),

('1','PC',true,15),
('2','PC',true,30),
('3','PC',false,10),
('4','PC',true,14),
('5','PC',false,40),
('6','PC',true,15),
('7','PC',true,12),
('8','PC',false,10),
('9','PC',true,13),
('10','PC',false,12),
('11','PC',true,10),
('12','PC',false,15),
('13','PC',true,15),
('14','PC',false,15),
('15','PC',false,25),
('16','PC',false,18),
('17','PC',false,20),

('1','EM',true,15),
('2','EM',true,300),
('3','EM',false,10),
('4','EM',true,25),
('5','EM',false,200),
('6','EM',true,12),
('7','EM',true,22),
('8','EM',false,10),
('9','EM',true,18),
('10','EM',false,120),
('11','EM',true,15),
('12','EM',false,15),
('13','EM',true,15),
('14','EM',false,50),
('15','EM',false,25),
('16','EM',false,25),
('17','EM',false,20)
;

INSERT INTO events(huid,room,building,date_req,description,start_time,end_time,recurring) VALUES
('11111111','3','MD',NOW(),'harvard engineering society','2010-5-1 14:00:00','2010-5-1 14:30:00',NULL),
('11111111','3','MD',NOW(),'harvard engineering society','2010-5-4 13:00:00','2010-5-4 14:00:00',NULL),
('11111111','3','MD',NOW(),'harvard engineering society','2010-5-4 15:00:00','2010-5-4 15:30:00',NULL)
;

