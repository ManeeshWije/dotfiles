zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit
fpath+=("$(brew --prefix)/share/zsh/site-functions")

export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh
export TERM="xterm-256color"
export EDITOR='nvim'
export VISUAL="nvim"
export HISTSIZE=10000
export SAVEHIST=10000

# Shortcuts
bindkey -v
bindkey '^R' history-incremental-search-backward
bindkey '^H' backward-delete-char
bindkey '^?' backward-delete-char

# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -m'
alias fetch='git fetch'
alias merge='git merge'
alias pull='git pull origin'
alias push='git push origin'
alias stats='git status'  # 'status' is protected name so using 'stats' instead
alias tag='git tag'
alias newtag='git tag -a'

alias luamake=/Users/maneesh/lua-language-server/3rd/luamake/luamake

export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# bun completions
[ -s "/Users/maneesh/.bun/_bun" ] && source "/Users/maneesh/.bun/_bun"

# bun
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$PATH"

export PATH="/opt/homebrew/opt/postgresql@15/bin:$PATH"
export PATH="$PATH:/Applications/Docker.app/Contents/Resources/bin/"

autoload -U promptinit; promptinit
prompt pure
