FROM fedora:42

# Pakete installieren
RUN dnf -y install cmake make automake gcc gcc-c++ kernel-devel git

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

ENTRYPOINT ["./test.sh"]