#!/bin/bash
# This script is run every time the cron job run

#
# Run the bacic Drupal cron job
#
wget -O - -q -t 1 http://localhost/cron.php?cron_key=EH-46MEnQ7aDGGXVLBrZeCfGaz6j7nuLlTJ4z79wB64

echo "Cronjob ran successfully"

