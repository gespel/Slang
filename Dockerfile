FROM archlinux:latest

# Pakete installieren
RUN pacman -Sy --noconfirm \
      cmake \
      make \
      automake \
      gcc \
      git \
#      linux-headers \
      bash 

# Arbeitsverzeichnis setzen
WORKDIR /app

# Projekt kopieren
COPY . .

# Build
RUN mkdir build \
    && cd build \
    && cmake .. -DSLANG_DEBUG=ON \
    && make \
    && cd .. \
    && make

# Testskript ausführbar machen
RUN chmod +x test.sh

ENTRYPOINT ["sleep", "infinity"]