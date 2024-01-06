#!/bin/bash

# Array of safe commands
commands=("echo 'Hello, World!'" "ls -l \$MY_VAR" "pwd" "date" "cat /etc/passwd" "ps aux" "whoami" "df -h" "uname -a" "uptime" "grep -q 'search' file.txt" "wc -l file.txt" "tar -czvf archive.tar.gz file.txt" "find . -name '*.txt'" "chmod +x script.sh" "mkdir -p \$EMPTY_VAR" "rm -rf old_directory" "cp file.txt backup/\$MY_VAR" "mv file.txt new_location/" "curl -O https://example.com/file.txt > /dev/null" "ls -R / | grep -q .txt" "head -n 10 file.txt" "tail -n 5 file.txt" "sort file.txt" "uniq file.txt" "sed 's/search/replace/' file.txt" "awk '{print \$1}' /etc/passwd" "cut -d: -f1 /etc/passwd" "echo 'Line 1\nLine 2\nLine 3' > multiline.txt" "cat multiline.txt | grep -q 'Line 2'" "export MY_VAR='some_value'" "unset MY_VAR" "env" "pwd")

# Array of operators
operators=(">" ">>" "<" "|")

# Array of environment variables
environment_variables=("SHLVL" "MY_VAR" "EMPTY_VAR")

# Function to generate a random environment variable
generate_random_env_var() {
  env_var_index=$((RANDOM % ${#environment_variables[@]}))
  echo "${environment_variables[env_var_index]}"
}

# Function to generate a random command
generate_random_command() {
  command_index=$((RANDOM % ${#commands[@]}))
  operator_index=$((RANDOM % ${#operators[@]}))
  env_var=$(generate_random_env_var)

  # Combine the selected command, operator, and environment variable
  if [ "${operators[operator_index]}" == ">" ] || [ "${operators[operator_index]}" == ">>" ]; then
    # Redirect output to a file
    random_command="${commands[command_index]} ${operators[operator_index]} output.txt"
  elif [ "${operators[operator_index]}" == "<" ]; then
    # Redirect input from a file
    random_command="${commands[command_index]} ${operators[operator_index]} input.txt"
  elif [ "${operators[operator_index]}" == "|" ]; then
    # Use pipe operator
    random_command="${commands[command_index]} ${operators[operator_index]} grep -q \$${env_var}"
  else
    # Use environment variable as an argument
    random_command="${commands[command_index]} \${env_var}"
  fi

  echo "$random_command"
}

# Number of commands to generate
num_commands=2500

# Generate and print random commands
for ((i=1; i<=$num_commands; i++)); do
  random_command=$(generate_random_command)
  echo "$random_command"
done
