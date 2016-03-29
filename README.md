###Võru keele HTS-kõnesüntesaator

           The HMM-Based Speech Synthesis Engine "hts_engine API"  
           developed by HTS Working Group                          
           http://hts-engine.sourceforge.net/                      

           All rights reserved.

           Redistribution and use in source and binary forms, with or
           without modification, are permitted provided that the following
           conditions are met:
          - Redistributions of source code must retain the above copyright
            notice, this list of conditions and the following disclaimer.
          - Redistributions in binary form must reproduce the above
            copyright notice, this list of conditions and the following
            disclaimer in the documentation and/or other materials provided
            with the distribution.
          - Neither the name of the HTS working group nor the names of its
            contributors may be used to endorse or promote products derived
            from this software without specific prior written permission.

           THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
           CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
           INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
           MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
           DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
           BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
           EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
           TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
           DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
           ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
           OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
           OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
           POSSIBILITY OF SUCH DAMAGE.

==============================================================================

                   Võru keele HTS-kõnesüntees                     
             Copyright (c) 2016 Eesti Keele Instituut              
              Liisi Piits, Sulev Iva, Indrek Kiissel
             
         HTK-3.4.1, HTS-2.3.patch, HTS-engine_API_1.10
             	                                        

==============================================================================
####Installimine:<br>

    	Peale lahtipakkimist

        cd synthts_vr-master/synthts_vr
        ./configure
        make


==============================================================================
####Kasutamine:<br>

		-f 		[sisendtekst utf8-s] 
		-o 		[väljund-wav] 
		-m 		[hääle nimi, vt kataloogi htsvoices/]
		-r 	[kõnetempo, double, 0.01-2.76]		
		
		näide:
		bin/synthts_et -o out_slv.wav -f in.txt -m htsvoices/eki_et_slv.htsvoice -r 1.1
