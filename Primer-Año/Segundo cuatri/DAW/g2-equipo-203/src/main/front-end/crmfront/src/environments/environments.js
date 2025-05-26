export const API_ENDPOINTS = Object.freeze({
  local : 'http://localhost:8080/app/api',
  javi  : 'http://35.188.206.158/api',
  jose  : 'http://34.16.53.60/api',
  pedro : 'http://34.133.224.82/api'
});

const TARGET = 'local';

export const BASE_URL = API_ENDPOINTS[TARGET];