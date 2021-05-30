#!/bin/bash

source /root/csce_3402/lab_1/backup_restore_lib.sh

validate_backup_params $@

backup $@
