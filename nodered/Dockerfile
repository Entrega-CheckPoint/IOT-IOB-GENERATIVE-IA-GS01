FROM nodered/node-red:latest

USER root

# Instala dependência
RUN apk add --no-cache libaio

# Copia o Oracle Client já descompactado
COPY instantclient_21_11 /opt/oracle/instantclient_21_11

# Define variável de ambiente com o path da lib
ENV LD_LIBRARY_PATH="/opt/oracle/instantclient_21_11"

USER node-red
