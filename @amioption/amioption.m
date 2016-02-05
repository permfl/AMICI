classdef amioption < matlab.mixin.SetGet
    %AMIOPTION Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        atol = 1e-16;
        rtol = 1e-6;
        maxsteps = 1e4;
        sens_ind@double;
        tstart = 0;
        lmm = 2;
        iter = 2;
        linsol = 9;
        stldet = 1;
        interpType = 1;
        lmmB = 2;
        iterB = 2;
        ism = 1;
        sensi_meth = 'forward';
        sensi = 0;
        nmaxevent = 10;
        ordering = 1;
        ss = 0;
    end
    
    methods
    end
    
end

