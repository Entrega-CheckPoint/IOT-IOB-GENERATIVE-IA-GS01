FROM nodered/node-red:latest

USER root

# Instala as dependências usando apk (Alpine Package Keeper)
RUN apk add --no-cache libaio unzip wget

# Instala o Oracle Instant Client
RUN mkdir -p /opt/oracle && \
    cd /opt/oracle && \
    wget https://download.oracle.com/otn_software/linux/instantclient/211000/instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    unzip instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    rm instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    echo "/opt/oracle/instantclient_21_10" > /etc/ld.so.conf.d/oracle-instantclient.conf && \
    ldconfig

USER node-red
