// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// in a CI environment we redefine "playsnd" function as a nop dummy
funcprot(0);
if getenv("CI","FALSE") <> "FALSE" then
	function playsnd(y),end
end

y = wavread('SCI/modules/sound/demos/chimes.wav');
playsnd(y); 

tab_ref = [
"世界您好",
"азеазея",
"ハロー・ワールド",
"เฮลโลเวิลด์",
"حريات وحقوق",
"תוכנית"];

for i = 1 : size(tab_ref,'*')
  mkdir(TMPDIR + filesep() + tab_ref(i));
  copyfile(SCI+'/modules/sound/demos/chimes.wav',TMPDIR + filesep() + tab_ref(i) + filesep() + tab_ref(i) +'.wav');
  y = wavread(TMPDIR + filesep() + tab_ref(i) + filesep() + tab_ref(i) +'.wav');
  playsnd(y); 
  mdelete(TMPDIR + filesep() + tab_ref(i) + filesep() + tab_ref(i) +'.wav');
  rmdir(TMPDIR + filesep() + tab_ref(i));
end
