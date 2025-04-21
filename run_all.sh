#!/bin/bash

# Define los parámetros para el algoritmo (ajusta según tus necesidades)
ALGORITHM="-greedy"  # Puedes cambiar a "-greedy" si prefieres
GRASP_N=5
ITERATIONS=100

# Crear la carpeta para los resultados si no existe
RESULTS_DIR="results"
mkdir -p $RESULTS_DIR

# Crear un archivo para los resultados dentro de la carpeta
RESULTS_FILE="$RESULTS_DIR/resultados.csv"
echo "Instancia,Vehículos,Tiempo Total,Tiempo CPU" > $RESULTS_FILE

# Ejecutar el programa para cada archivo en la carpeta instances
for file in instances/*; do
  if [ -f "$file" ]; then
    echo "Procesando $file..."
    
    # Ejecutar el programa con los parámetros adecuados
    #output=$(./bin/daa-prs "$file" $ALGORITHM)
    output=$(./bin/daa-prs "$file")

    # Extraer la línea de resultado (la que comienza con RESULTADO)
    result_line=$(echo "$output" | grep "^RESULTADO")
    
    if [ ! -z "$result_line" ]; then
      # Eliminar la palabra "RESULTADO," y agregar al archivo de resultados
      result=$(echo "$result_line" | sed 's/^RESULTADO,//')
      echo "$result" >> $RESULTS_FILE
    else
      echo "Error: No se encontraron resultados para $file"
      echo "$(basename $file),ERROR,ERROR,ERROR" >> $RESULTS_FILE
    fi
  fi
done

echo "Procesamiento completado. Resultados guardados en $RESULTS_FILE"

# Mostrar un resumen
echo ""
echo "Resumen de resultados:"
cat $RESULTS_FILE