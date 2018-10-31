//  Scicos
//
// Copyright (C) INRIA - METALAU Project <scicos@inria.fr>
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// See the file ../license.txt
//

function tree_show(x,titletop)

    if nargin < 1 then
        error(sprintf(_("%s: Wrong number of input arguments: %d to %d expected.\n"), "tree_show", 1, 2));
    end

    if type(x)<>16 & type(x)<>17 & type(x)<>15 & type(x)<>128 then
        error("Wrong type; input must be a list or an Xcos object.")
    end

endfunction


function java = crlist3(x,Path, java)
    if type(x)==15 then
        II=1:size(x);v=string(II);
    else
        v=getfield(1,x);
        if type(x)==17 & v(1)=="st" then
            II=3:size(v,"*");
        else
            II=2:size(v,"*");
        end
    end
    for i=II
        path=Path+","+string(i)
        titre=v(i);
        o=getfield(i,x);
        if type(o)==16 | type(o)==17 | type(o)==128 then
            w=getfield(1,o);
            titre2=titre+" ("+w(1)+")";
            currentNode = uiCreateNode(titre2);
            currentNode = crlist3(o,path,currentNode); //* recursive
            java = uiConcatTree(java, currentNode);

        elseif type(o)==15 then
            titre2=titre;
            currentNode = uiCreateNode(titre2);
            currentNode = crlist3(o,path,currentNode); //* recursive
            java = uiConcatTree(java, currentNode);
        else
            try
                if size(o, "*") > 40 then
                    tts = typeof(o) + " of size " + sci2exp(size(o))
                else
                    tts = sprintf("%s", sci2exp(o))
                end,
            catch
                tts = typeof(o);
            end
            titre2=titre+": "+tts  ;
            java = uiConcatTree(java, uiCreateNode(titre2));
        end
    end

endfunction
