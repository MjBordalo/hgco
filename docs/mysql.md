# MySql

## Instalation
## Common Linux Commands
### Start
`mysql -h <host> -u <user> -p <select_the_database>`
### Check status
`service mysql status`
### Other Commands
### Backup & Restore
Backup as mysql `root` user the `archive` db to `archive_bkp` document

` mysqldump-u root -p archive >archive_bck.sql`


Restore to `archive` db

`mysql -u archive -p archive < archive_22_02_2017.sql`


## MySql commands

### Other Commands
Show databases;
Show tables;

USE <nome_database>;

SHOW GLOBAL VARIABLES LIKE 'PORT';

mostrar users:
select User,Host from mysql.user;
SELECT User, Host, Db FROM db;

