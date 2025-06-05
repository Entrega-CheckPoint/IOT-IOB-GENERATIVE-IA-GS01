FROM nodered/node-red:latest

USER root

# Instala dependência obrigatória
RUN apk add --no-cache libaio

# Copia a pasta já descompactada
COPY instantclient_21_11 /opt/oracle/instantclient_21_11

# Configura o Oracle Instant Client
RUN echo "/opt/oracle/instantclient_21_11" > /etc/ld.so.conf.d/oracle-instantclient.conf && \
    ldconfig

USER node-red
