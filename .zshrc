zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit

if [[ "$OSTYPE" == "darwin"* ]]; then
    fpath+=("$(brew --prefix)/share/zsh/site-functions")
fi

export NVM_DIR=~/.nvm
export TERM="xterm-256color"
export EDITOR='nvim'
export VISUAL="nvim"
export HISTFILE=~/.zsh_history
export HISTSIZE=10000
export SAVEHIST=10000

setopt appendhistory
setopt sharehistory
setopt incappendhistory
setopt hist_ignore_all_dups
setopt hist_save_no_dups
setopt hist_ignore_dups
setopt hist_find_no_dups

# Shortcuts
bindkey -v
bindkey '^R' history-incremental-search-backward
bindkey '^p' history-search-backward
bindkey '^n' history-search-forward
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

alias st='syncthing'
alias sd="cd ~ && cd \$(find --type d | fzf)"
alias yy='yazi'
alias paccache='sudo pacman -Scc && yay -Scc'
alias pacdelete='pacman -Qtdq | sudo pacman -Rns -'

if [[ "$OSTYPE" == "darwin"* ]]; then
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
    export PATH="$PATH:/Applications/Docker.app/Contents/Resources/bin/:/Users/maneesh/Library/Python/3.11/bin:/opt/homebrew/opt/postgresql@15/bin:/Users/maneesh/.config/scripts/"
fi

# bun
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$HOME/.config/scripts:$PATH"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # bun completions
    [ -s "/home/maneesh/.bun/_bun" ] && source "/home/maneesh/.bun/_bun"
fi

. "$HOME/.cargo/env"

autoload -U promptinit; promptinit

prompt pure
