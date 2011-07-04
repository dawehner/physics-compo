load -ascii output-rho.dat
#load -ascii output-u.dat

set(0, 'defaultfigurevisible', 'off');


z_size = 0.33
dim = size(output_rho)

columns = dim(2)

for i=[1:columns]
	x(i) = i * z_size
end

for i=[1:dim(1)]
	if (rem(i, 250) == 0)
		plot(x,output_rho(i,:), "@1")
		axis([0,70,0,20])
		filename=sprintf('%06d.png', i)
		print(filename)
	end
	
end

for i=[1:dim(1)]
	if (rem(i, 250) == 0)	
	#	plot(x,output_u(i,:), "@1")
	#	filename=sprintf('%06d-u.png', i)
	#	print(filename)
	end
end
