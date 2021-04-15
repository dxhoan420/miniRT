# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    render_all_bmp_in_scenes.sh                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dxhoan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 14:02:12 by dxhoan            #+#    #+#              #
#    Updated: 2021/04/15 14:34:13 by dxhoan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

files=($(find -E ./scenes -type f -regex "^.*$"))
for item in ${files[*]}
do
	./miniRT $item --save
	#parallel -N0 ./miniRT $item --save
done
