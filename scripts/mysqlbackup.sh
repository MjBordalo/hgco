DATE=$(date +"%Y_%m_%d-%H_%M")
echo "backing up Mysql  at $DATE"

cd ~/hgco
mysqldump -u root -pgreen archive > archive_bck_$DATE.sql
