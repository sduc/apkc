 #!/usr/local/bin/python
import sys
import os

if len(sys.argv) > 1 and sys.argv[1] == "big":
  a = "174316498273647891264182764916"
  b = "138971038947123471239048723"
  n = "1000000"
else :
  if len(sys.argv) < 4:
    print("need at least three arguments : a , b , n")
    sys.exit()
  a = sys.argv[1]
  b = sys.argv[2] 
  n = sys.argv[3]

baseIn = sys.argv[4] if len(sys.argv) > 4 else str(10)

print("our add : ")
os.system("time((echo "+a+" | ./chgbase "+baseIn+" 16 ; echo "+b+" | ./chgbase "+baseIn+" 16) | ./add "+n+" | ./chgbase 16 10)") 
print("check sum : ")
os.system("(echo "+a+" | ./chgbase "+baseIn+" 10 ; echo "+b+" | ./chgbase "+baseIn+" 10) | ./checkadd "+n) 
print("bad add : ")
os.system("time((echo "+a+" | ./chgbase "+baseIn+" 10 ; echo "+b+" | ./chgbase "+baseIn+" 10) | ./badadd "+n+")") 
