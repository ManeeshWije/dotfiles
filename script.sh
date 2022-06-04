#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/maneeshwijewardhana/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"
# install everything
brew install ripgrep fzf ccls clang-format cmake cmatrix git go heroku htop llvm lua mongosh ncdu neofetch neovim node nvm pfetch python speedtest-cli starship tmux tty-clock audacity balenaetcher brave-browser firefox caffeine discord iterm2 microsoft-teams minecraft slack spotify visual-studio-code zoom 
# vim plug
sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
ssh-keygen -t ed25519 -C "m.mwije1@gmail.com"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

# clone projects
# cd Documents
# mkdir Projects
# cd Projects
# git clone git@github.com:ManeeshWije/Personal-Website.git && git clone git@github.com:ManeeshWije/Tasker.git && git clone git@github.com:ManeeshWije/GoChat.git && git clone git@github.com:ManeeshWije/pokedex.git && git clone git@github.com:ManeeshWije/abby.git && git clone git@github.com:ManeeshWije/application-tracker.git && git clone git@github.com:ManeeshWije/Reduction.git && git clone git@github.com:ManeeshWije/GetBack2Wrk.git && git clone git@github.com:ManeeshWije/twitterLikeBot.git && git clone git@github.com:ManeeshWije/Baby-Talk.git
