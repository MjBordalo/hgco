## Backup:
mysqldump -u root -p archive > archive_bck_DD_MM_YYYY.sql

#Restore:
mysql -u archive -p  archive < archive_22_02_2017.sql


see crontab for scheduling
