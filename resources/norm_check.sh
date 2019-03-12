if [ $1 -eq $2 ]
then
	echo "please specifiy single location"
else
	cat $1/* | rev | cut -c 1-3 | grep "&"
	cat $1/* | rev | cut -c 1-3 | grep "|"
	cat $1/* | rev | cut -c 1-3 | grep "+"
	cat $1/* | rev | cut -c 1-3 | grep "-"
	cat $1/* | rev | cut -c 1-3 | grep "*"
	cat $1/* | rev | cut -c 1-3 | grep "/"
	cat $1/* | rev | cut -c 1-3 | grep "="
	cat $1/* | rev | cut -c 1-3 | grep ">>"
	cat $1/* | rev | cut -c 1-3 | grep "<<"
fi
