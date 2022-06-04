zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit

export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh
export TERM="xterm-256color"
export EDITOR='nvim'

# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -m'
alias fetch='git fetch'
alias pull='git pull origin'
alias push='git push origin'
alias stats='git status'  # 'status' is protected name so using 'stats' instead
alias tag='git tag'
alias newtag='git tag -a'

alias rr='curl -s -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash'
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'

eval "$(starship init zsh)"
