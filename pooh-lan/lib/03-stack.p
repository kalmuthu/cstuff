# test stack data structure - stack.inc

include 'stack.inc'

println( ~msg 'stack of numbers' )

l = make_stack()

l . push( ~data 1 )
l . push( ~data 2 )
l . push( ~data 3 )
l . push( ~data 4 )


while  l . count() != 0
  r = l . pop( )
  println( ~msg r )
end

println( ~msg 'stack of arrays' )

l . push( ~data [ 1, 2] )
l . push( ~data [ 2, 3] )
l . push( ~data [ 3, 4] )
l . push( ~data [ 5, 6] )

while  l . count() != 0
  r = l . pop( )
  println( ~msg join( ~array r ~separator ' - ' ) )
end



print( ~msg '*** eof stack test ***' )



