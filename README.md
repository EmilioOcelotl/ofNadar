# ofNadar

## Interacción 

1, 2 o 3 para selccionar el video. 

p para reproducir.

s para detener.

h para ocultar.

H para mostrar. 

## png a video con transparencia

Primero hay que renombrarlas con números consecutivos 

ls -v | cat -n | while read n f; do mv -n "$f" "$n.png"; done

Luego hay que rellenar con ceros

rename 's/\d+/sprintf("%06d",$&)/e' *

Luego convertir a un formato de video con alpha

ffmpeg -r 60 -i %06d.png -c:v hap -format hap_alpha -compressor snappy nadar3.mov

