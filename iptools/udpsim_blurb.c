#include <stdio.h>
#include <stdlib.h>

void print_help() {
  fprintf(stderr,"%s",
	"udpsim [-d] -x <capture_file> -c <capture-host> -i <tx-interface> [-p <tx-substitution-port>] [-r <tx-substitution-port-range>] [-f <outgoing-filter-expression>] [-n]\n"
	"\n"
	"Resends outgoing UDP traffic from capture file.\n"
	"\n"
	"Only traffic that originates from one IP address in the capture can be sent out by this tool, so that we will not be able to\n"
	"collide with real traffic on the current network segment.\n"
	"\n"
	"The simulator performs the following steps:\n"
	"\n"
	"- The simulator loops over all packet contained in the input capture file\n"
	"- if the source ip address of a packet is equal to <capture-host> value, then it is selected. Only selected packets\n"
	"  will be sent by the simulator (Please see -c <capture-host> parameter)\n"
	"- If a filter expression (-f option) is specified then only those packets from the capture that satisfy the filter are selected.\n"
	"- All selected packets are subjected to optional substitution rules (-r option);\n"
	"  The first mandatory substitution rule adjusts the source ip of outgoing packet to that\n"
	"  of an existing network interface (-i <tx-interface> options)\n"
	"  Substituion rules specified by -r <rule_syntax> option can modify the destion port and\n"
	"  destination ip address of outgoing packets.\n"
	"- An effort is made to send the packets with the same timing as those included in the capture is made.\n"
	"- During the simulation run we capture all packets that conform to the filter expression; this way the response is recorded.\n"
	"\n"
	"An error is reported if source port of selected packet collides with already bound port.\n"
	"\n"
	"Arguments:\n"
	"\n"
	"\n"
	"The substution rule file includes the following directives:\n"
	"\n"
	"-x <capture_file>\n"
	"	the capture file in libpcap format (written by tcpdump).\n"
	"	This parameter is mandatory.\n"
	"\n"
	"-c <capture_host>\n"
	"	Only packets contained in the capture, where source ip address is equal to <capture_host> will be sent out.\n"
	"	This parameter is mandatory.\n"
	"\n"
	"-i <tx-interface>\n"
	"	IP address of a network interface on the current system.\n"
	"	When sending out a replayed packet, the <capture-host> is substituted with <tx-interface>\n"
	"	This parameter is mandatory.\n"
	"\n"
	"-f <outgoing-filter-expression>\n"
	"	Filter expresssion that is applied to all packets on this capture; only packets that fit this filter will be sent out.\n"
	"	This parameter is optional.\n"
	"	For syntax of filter expression see see man pcap-filter(7)\n"
	"\n"
	"-r [src-port|dst-port],<capture-port>,<real-port>\n"
	"	This option specifies an port substituion rule for a an outgoing packet.\n"
	"	This parameter applies either to the destination port (if first token is dst) or the source port (if first token is src)\n"
	"	When sending a packet, the <capture-port> port number from the capture file will be substituted with value <real-port>\n"
	"	This parameter is optional, multiple occurences of this option add up.\n"
	"\n"
	"-r [src-port-range|dst-port-range],<capture-port-start>,<capture-port-end>,<real-port-start>\n"
	"	This option specifies an port substituion rule for outgoing packets.\n"
	"	This parameter applies either to the destination port (if first token is dst) or the source port (if first token is src)\n"
	"	When sending a packet, the range of port numbers starting with <capture-port-start> and ending with <capture-port-end>\n"
	"        from the capture file will be substituted with value <real-port>+<port in packet from capture>-<capture-port-start>\n"
	"	This parameter is optional, multiple occurences of this option add up.\n"
	"\n"
	"-r dst-ip,<destination-ip-address-in-capture>,<real-destination-ip-address>\n"
	"	This option specifies an port ip address substitution rule for outgoing packets.\n"
	"	The destination ip address of\n"
	"\n"
	"-o <output capture file>\n"
	"        This parameter is optional.\n"
	"	File name of capture file of incoming packets.\n"
	"        If this option is missing then the capture file will be stored in a file name derived from input file name as\n"
	"        <input_capture_file>.in.cap\n"
	"\n"
	"-y <input capture filter>\n"
	"	This parameter is optional.\n"
	"	An expression that is added to capture filter of incoming packets.\n"
	"	By default the capture filter of incoming packets is udp and dst <tx-interface>. If this parameter is present\n"
	"        then its value is added to the default capture filter and it is set to udp and <input capture filter>\n"
	"	For syntax of filter expression see see man pcap-filter(7)\n"
	"\n"
	"-n\n"
	"	No packet capture is performed during this run.\n"
	"\n"
	"\n"
	"-d\n"
	"	Dry run. No packets are sent during dry run (enabled with -d option); No capture files are created during dry run.\n"
	"	Packets data is displayed if it is sent during a siumulation run.\n"
	"	If the source port of an outgoing packet collides with an UDP port in use, then this command exits with error (status 1).\n"
	"	Please note that the list of ports in use at the moment of invoking this command are considered.\n"
	"\n"
	"\n"
	"Limitations - Linux:\n"
	"	user of this program must have root access.\n"
	"\n"
	"	The program tests if outgoing packets would clash with a bound port, alas list of ports is obtained at start of program run,\n"
	"	this information may not be up to date during the entire simulation run.\n"
	"\n"
	"	The tool gives the possibility to manipulate the ip addresses and port numbers of outgoing packets, relative to that of the capture.\n"
	"	Not all application protocols may allow for such treatment; if your application protocol creates a checksum over the ip or udp headers,\n"
	"        then modification of these parameters will break the checksum (for example IPSEC like protocol over UDP would break).\n"
	"\n"
	"	On some kernel versions (2.6.18) you will have to run 32 bit version of udpsim on the 32 bit kernel, and 64 bit version on 64 bit kernel.\n"
	"	This is since tpacket_hdr structure (from linux/if_packet.h) is shared between kernel and user space and has long in it.\n"
	"	When in doubt then please rebuild libpcap and udpsim from the sources.\n"
	"\n"
	"\n"
	"Limitations - Windows:\n"
	"        Cygwin must be installed (download here http://cygwin.org/ ) and cygwin/bin directory must be in the path.\n"
	"	Winpcap must be installed (download here http://www.winpcap.org/ ) - it is also installed as part of wireshark setup.\n"
	"	We can't capture traffic on loopback adapter (winpcap limitation)\n"
	"\n"
	"\n"
	"Example usage:\n"
	"\n"
	"\n"
	"./udpsim -x TEST10_HOST-B.cap -c 10.36.4.112 -i 127.0.0.1 -f 'dst 10.36.4.161' -r dst-port,2000,12321 -r dst-ip,10.36.4.161,127.0.0.1\n"
	"\n"
	"Uses capture file TEST10_HOST-B.cap (option: -x TEST10_HOST-B.cap)\n"
	"\n"
	"The following packets are selected to be sent, (all restrictions do apply).\n"
	"  Packet must be udp packet.\n"
	"  the source ip address must be 10.36.4.112 (option: -c 10.36.4.112)\n"
	"  the destination ip address must be 10.36.4.161 (option: -f 'dst 10.36.4.161')\n"
	"\n"
	"The selected packets are then modified.\n"
	"  The source ip address is set to 127.0.0.1 (option: -f 127.0.0.1)\n"
	"  The destination port is changed from 2000 to 12321 (option: -r dst-port,2000,12321)\n"
	"  The destination address is changd to 127.0.0.1 (option: -r dst-ip,10.36.4.161,127.0.0.1)\n"
	"\n"
	"Incoming packets are captured by the following default filter: udp and dst 127.0.0.1\n"
	"Incoming packets are captured in file TEST10_HOST-B.cap.in.cap\n"
	"\n"
	"\n"
	"\n"
	"./udpsim -x TEST10_HOST-B.cap -c 10.36.4.112 -i 127.0.0.1 -f 'dst 10.36.4.161' -r dst-port,2000,12321 -r dst-ip,10.36.4.161,127.0.0.1  -o in.cap -y \"port 12321\"\n"
	"\n"
	"Differences to the previous case:\n"
	"\n"
	"Incoming packets are captured by the following default filter: udp and dst 127.0.0.1 and port 12321\n"
	"Incoming packets are captured in file in.cap\n"
	"\n"
	"\n"
  );
  exit(1);
}  
