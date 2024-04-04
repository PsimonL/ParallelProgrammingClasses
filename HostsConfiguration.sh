#!/bin/bash
# WŁASNE opracowanie instrukcji na podstawie podanej instrukcji przez prowadzącego - Dr inż. Piotr Gronek: https://view.fis.agh.edu.pl/staff/gronek/

# =========================================================
#
#   WFiIS - laboratorium programowania równoległego MPI
#
# =========================================================
# Uruchamianie aplikacji MPICH MPI na klastrze stacji stud...
#         w pracowni komputerowej 204 (D-10).
#

# Logowanie na konta na hostach wydziałowych (AGH WFiIS) korzystając z personalnych credentiali.

# 0. Przejście do odpowiedniego pliku:
cd /opt/nfs/config/README.MPI

# 1. Jeśli nie ma folderu ~/.ssh to:
mkdir -p ~/.ssh
chmod 700 ~/.ssh
cd ~/.ssh

# 2.Towrzenie klucza:
ssh-keygen -t ecdsa
# Defaultowe wartości, ENTER na wszystkie pytania

# 3. Kopiowanie nowo wygenerowanego klucza do pliku authorized_keys:
cp id_ecdsa.pub authorized_keys

# 4. Uruchomienie agenta SSH:
eval "$(ssh-agent -s)"

# 5. Dodanie klucza do agenta:
ssh-add
# Powinno wydrukować, że klucz został dodany, jeżeli nic to może klucz ma inną nazwę niż domyśną, wtedy:
ssh-add ~/.ssh/moj_klucz_prywatny

# 7. Pierwsze logowanie na wszystkie stacje pokolei:
/opt/nfs/config/station204_name_list.sh 1 16
# 16 razy yes

# 8. Jeszcze raz i powinno już nie pytać o potwierdzenie:
/opt/nfs/config/station204_name_list.sh 1 16
# Potencjalny wydruk: zakres testowanych stacji - np. od stud204-01 do stud204-16: 
# stud204-01
# stud204-02
# stud204-03
# stud204-04
# stud204-05
# stud204-06
# stud204-07
# stud204-08
# stud204-09
# stud204-10
# stud204-11
# stud204-12
# stud204-13
# stud204-14
# stud204-15
# stud204-16

# 9. Weryfikacja połączenia zweotnego skryptem
/opt/nfs/config/station204_back_test.sh 1 16
# Testing SSH connections back to: stud204-...
# (...)
# No. of active stations: 16

# 10. Konfiguracaj wybranego pakietu MPI:
# Przykład - skrypt dla pakietu MPICH 4.2.0 i CUDA 12.1 (pracownia 204)
source /opt/nfs/config/source_mpich420.sh
source /opt/nfs/config/source_cuda121.sh
# Przykład - skrypt dla pakietu MPICH 3.2 (tylko Taurus)
source /opt/nfs/config/source_mpich32.sh

# 11. Kompilacja aplikacji:
mpicc helloMPI.c -o helloMPI

# 12. Przed każdym uruchomieniem programu MPI - ustalić aktualną listę dostępnych węzłów klastra
/opt/nfs/config/station204_name_list.sh 1 16 > nodes
cat nodes

# 13. Aplikacja MPI - uruchomienie na wszystkich dostępnych węzłach klastra po dwa procesy programu MPI, co zadziała po zrealizowaniu wszystkich powyższych podpunktów w podanej kolejności 1-13: 
mpiexec -f nodes -n $(( 2 * $(cat nodes | wc -l) )) ./helloMPI
# Przykładowy wydruk:
# (...)
# Hello, world! This is MPI process 2 of 16 on node stud204-03
# Hello, world! This is MPI process 11 of 16 on node stud204-12
# Hello, world! This is MPI process 5 of 16 on node stud204-06
# Hello, world! This is MPI process 6 of 16 on node stud204-07
# (...)