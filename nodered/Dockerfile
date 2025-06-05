FROM nodered/node-red:latest

USER root

# Instala dependências
RUN apt-get update && apt-get install -y libaio1 unzip wget

# Baixa e instala o Oracle Instant Client
RUN mkdir -p /opt/oracle && \
    cd /opt/oracle && \
    wget https://download.oracle.com/otn_software/linux/instantclient/211000/instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    unzip instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    rm instantclient-basiclite-linux.x64-21.10.0.0.0dbru.zip && \
    echo "/opt/oracle/instantclient_21_10" > /etc/ld.so.conf.d/oracle-instantclient.conf && \
    ldconfig

USER node-red
