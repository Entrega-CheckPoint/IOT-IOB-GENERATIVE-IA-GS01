FROM nodered/node-red:latest

USER root

# Instala dependências
RUN apk add --no-cache libaio unzip libc6-compat build-base python3

# Copia e extrai o Instant Client
COPY instantclient-basic-linux.x64-21.11.0.0.0dbru.zip /opt/oracle/
RUN cd /opt/oracle && \
    unzip instantclient-basic-linux.x64-21.11.0.0.0dbru.zip && \
    rm instantclient-basic-linux.x64-21.11.0.0.0dbru.zip && \
    ln -s instantclient_21_11 /opt/oracle/instantclient

# Copia a pasta SDK/include (mesmo sendo 19.27) para uso do oracledb
COPY sdk/include /opt/oracle/instantclient/sdk/include

# Variáveis de ambiente pro oracledb
ENV LD_LIBRARY_PATH=/opt/oracle/instantclient
ENV OCI_LIB_DIR=/opt/oracle/instantclient
ENV OCI_INC_DIR=/opt/oracle/instantclient/sdk/include

# Instala o módulo Node.js
RUN npm install oracledb@5.5.0 --unsafe-perm && \
    npm install node-red-contrib-oracledb@0.5.1 --unsafe-perm

USER node-red
