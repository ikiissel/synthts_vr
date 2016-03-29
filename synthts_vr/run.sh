#!/bin/bash

#   -f      [sisendtekst utf8-s] 
#   -o      [väljund-wav] 
#   -m      [hääle nimi, vt kataloogi htsvoices/]
#   -r      [kõnetempo, double, 0.01-2.76]
#   -debug  [prindi labeli struktuur]

bin/synthts_vr -o out_slv.wav -f in.txt -m htsvoices/eki_et_slv.htsvoice -r 1.1
bin/synthts_vr -o out_hll.wav -f in.txt -m htsvoices/eki_et_hll.htsvoice -r 1.1


