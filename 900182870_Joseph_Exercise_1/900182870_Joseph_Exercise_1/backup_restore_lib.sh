validate_backup_params(){

	if [ $# -eq 0  ]
	then
		echo "You did not enter any argumnet ! ./backup.sh [path of the directory to be backed up] [path of the directory to store the backup in] [encryption key]"
		exit 1
	elif [ ! $# -eq 3 ]
	then
		echo "You should enter 3 params but you entered $#"
		exit 1
	else
		valid=1
		
		for var in "$@"
		do
			if [ ! -d $var ] && [ $var != $3 ]
			then
				valid=0
				echo "$var is not a valid directory"
			fi
		done

		if [ $valid -eq 0 ];
		then
			echo "Please enter valid directories"
			exit 1
		fi

		cd $1

		if [ $(ls -l | wc -l ) -eq 1 ];
		then
			valid=0
			echo "Please enter a path for a non empty directory to back it up"
		fi

		if [ $valid -eq 0 ];
		then
			exit 1
		fi 




	fi
}

validate_restore_params(){
	
	if [ $# -eq 0  ]
	then
		echo "You did not enter any argumnet ! ./backup.sh [path og the backup directory] [path of the restore directory] [decryption key]"
		exit 1
	elif [ ! $# -eq 3 ]
	then
		echo "You should enter 3 params but you entered $#"
		exit 1
	else
		valid=1
		
		for var in "$@"
		do
			if [ ! -d $var ] && [ $var != $3 ]
			then
				valid=0
				echo "$var is not a valid directory"
			fi
		done


		if [ $valid -eq 0 ];
		then
			echo "Please enter valid directories paths"
			exit 1
		fi 

		cd $2

		if [ ! $(ls -l | wc -l ) -eq 1 ];
		then
			valid=0
			echo "Please enter a path for an empty directory to restore files in"
		fi

		cd ..

		cd $1

		if [ $(ls -l | wc -l ) -eq 1 ];
		then
			valid=0
			echo "Please enter a path for a non empty directory to restore it"
		fi

		if [ $valid -eq 0 ];
		then
			exit 1
		fi 


	fi

}

backup(){
	d=$(date|sed s/\ /_/g | sed s/\:/_/g)
	args=("$@")
	cd ${args[1]}
	mkdir $d
	dest_dir=${args[1]}/$d
	cd ${args[0]}
	directory=${args[0]}/*
	pass=${args[2]}

	for dir in $directory
	do
		if [ -d $dir ]
		then
			dir=${dir##*/}
			new_name=$dir.tar.gz
			tar -cvzf $new_name $dir
			echo $pass | gpg --batch -c --passphrase-fd 0 $new_name
			gpg_file=$new_name.gpg
			rm -d $new_name
			new_dir_name=$dir\_$d.tgz
			mv $gpg_file $new_dir_name
			mv $new_dir_name $dest_dir
		fi
	done
	

	name=allFiles.tar

	for file in $directory
	do
		if [ -f $file ]
		then
			file=${file##*/}
			tar -uvf $name $file
		fi
	done

	new_name=allFiles.tar.gz
	tar -cvzf $new_name $name
	rm -f $name
	echo $pass | gpg --batch -c --passphrase-fd 0 $new_name
	gpg_file=$new_name.gpg
	rm -d $new_name
	new_dir_name=allFiles_$d.tgz
	mv $gpg_file $new_dir_name
	mv $new_dir_name $dest_dir

}

restore(){

	args=("$@")
	cd ${args[1]}
	mkdir temp
	pass=${args[2]}
	cd ${args[0]}
	backup_dir=${args[0]}/*

	for dir in $backup_dir
	do

		dir=${dir##*/}
		enc=$(file $dir | grep "encrypted")

		if [ ! -z "$enc"  ]
		then
			new_dir=(${dir//_/ })
			tgz_file=${new_dir[0]}.tgz
			gpg --pinentry-mode loopback --passphrase $pass --output $tgz_file --decrypt $dir
			mv $tgz_file ${args[1]}/temp
		fi
	done

	cd ${args[1]}/temp
	cat *.tgz | tar zxvf - -i
	rm -d *.tgz
	mv * ${args[1]}
	cd ..
	rm -r temp
	tar -xvf allFiles.tar
	rm -d allFiles.tar

}
