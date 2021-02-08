
In order to use this program:

1) For backup from the command line use the following command:

/root/csce_3402/lab_1/backup.sh /root/csce_3402/lab_1/dir_to_backup /root/csce_3402/lab_1/dir_to_backup_into 123

This command will run the file backup.sh and pass to it three parameters :

1- the directory that we want to backup
2- the directory we want to put the backup into
3- the password for encryption. here we used 123 as an example for the password

2) For restore from the command line use the following command:

/root/csce_3402/lab_1/restore.sh /root/csce_3402/lab_1/dir_to_backup_into/(the name of the version you want to back it up ex: Mon_08_Feb_2021_06_41_01_PM_EET/) /root/csce_3402/lab_1/dir_to_restore_into/ 123

This command will run the file restore.sh and pass to it three parameters :

1- the directory that includes the backups
2- the directory we want to restore into
3- the password for decryption. here we used 123 as an example for the password


Note: Do not provide a non empty directory to the program to restore the files in because it will not allow so.
