FROM nodered/node-red:latest

USER root

# Instala dependências necessárias
RUN apk add --no-cache libaio unzip

# Copia o arquivo zipado
COPY instantclient-basic-linux.x64-21.11.0.0.0dbru.zip /opt/oracle/

# Extrai o conteúdo corretamente
RUN cd /opt/oracle && \
    unzip instantclient-basic-linux.x64-21.11.0.0.0dbru.zip && \
    rm instantclient-basic-linux.x64-21.11.0.0.0dbru.zip && \
    ln -s instantclient_21_11 /opt/oracle/instantclient && \
    echo "/opt/oracle/instantclient" > /etc/ld.so.conf.d/oracle-instantclient.conf || true

ENV LD_LIBRARY_PATH="/opt/oracle/instantclient"

USER node-red
