FROM archlinux:latest

# Pakete installieren
RUN pacman -Sy --noconfirm archlinux-keyring && \
    pacman -Sy --noconfirm \
      cmake \
      make \
      automake \
      clang \
      git \
      meson \
      zsh \
      gdb

RUN chsh -s /bin/zsh

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

RUN echo 'alias build="rm -rf build && meson setup build && ninja -C build"' >> ~/.zshrc
RUN echo 'export PATH="/workspaces/Slang/build:$PATH"' >> ~/.zshrc
RUN echo 'echo "==================================================================================================================="' >> ~/.zshrc
RUN echo 'echo "Welcome to the Slang development environment! Run \"build\" to compile and \"slang\" to run the executable."' >> ~/.zshrc
RUN echo 'echo "==================================================================================================================="' >> ~/.zshrc
ENTRYPOINT ["sleep", "infinity"]