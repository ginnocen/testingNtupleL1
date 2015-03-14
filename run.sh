time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersHadEt_HF")
EOI
time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersHadEt_barrel")
EOI
time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersHadEt_endcap")
EOI




time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersEmEt_HF")
EOI
time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersEmEt_barrel")
EOI
time root -b > an.log 2>&1 <<EOI
.x compareMCData.C("hTowersEmEt_endcap")
EOI


