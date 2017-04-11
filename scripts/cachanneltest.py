#!/usr/bin/env python

from CaChannel import CaChannel, CaChannelException
try:
    chan = CaChannel('miHost:ExpString')
    chan.searchw()
    chan.putw('ExperienciaPython')
    geti= chan.getw()
except CaChannelException as e:
    print(e)

print geti
