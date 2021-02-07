source ./backup_restore_lib.sh

args=("$@")

validate_backup_params $@

backup $@
