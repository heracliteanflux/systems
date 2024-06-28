# ~/.bashrc
#
# ~/.bashrc runs in interactive shells
#   1. local  non-login interactive shell (e.g., bash)
#   2. remote     login interactive shell (e.g., ssh)

##############################
#
#     SHELL-AGNOSTIC
#
##############################
source "$HOME/.shell_env"
source "$HOME/.shell_interactive"

##############################
#
#     BASH-SPECIFIC
#
##############################
source "$HOME/.bash_env"
source "$HOME/.bash_interactive"
