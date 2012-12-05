clc; clear all;
syms FCY TCY TAD; FCY=40000000; TCY=1/FCY; TAD=0.000000075; ADCS=TAD/TCY -1

%% Kinematic Calculations
clc; clear all;

% PPR: Pulse Per Revolution
% GR: Gear Ratio
% D: Diameter
% C: Circumference
% DSP: Distance traveled per QEI pulse
% CS: Cell size
% CC: Cell center

syms PPR GR D C DSP; 
format longe
PPR=2048, GR=40/12, D=22, C=pi*D, DSP=C/(PPR*GR), CS=160, CC=CS/DSP,