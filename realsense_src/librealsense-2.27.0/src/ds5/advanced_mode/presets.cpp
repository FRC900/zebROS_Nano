// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2017 Intel Corporation. All Rights Reserved.

#include "presets.h"

namespace librealsense
{
    void default_400(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 500;
        p.depth_controls.deepSeaNeighborThreshold = 7;
        p.depth_controls.deepSeaSecondPeakThreshold = 325;
        p.depth_controls.lrAgreeThreshold = 24;
        p.depth_controls.minusDecrement = 10;
        p.depth_controls.plusIncrement = 10;
        p.depth_controls.scoreThreshA = 1;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 4.f;
        p.rsm.removeThresh = 63;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 3;
        p.rsvc.minSouth = 1;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 51;
        p.rctc.rauDiffThresholdRed = 51;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 60;
        p.spc.sloK1PenaltyMod1 = 105;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 190;
        p.spc.sloK2PenaltyMod2 = 130;
        p.hdad.lambdaAD = 800.f;
        p.hdad.lambdaCensus = 26.f;
        p.cc.colorCorrection1 = 0.4620000123978f;
        p.cc.colorCorrection2 = 0.5400000214577f;
        p.cc.colorCorrection3 = 0.5400000214577f;
        p.cc.colorCorrection4 = 0.2080000042915f;
        p.cc.colorCorrection5 = -0.3319999873638f;
        p.cc.colorCorrection6 = -0.2129999995232f;
        p.cc.colorCorrection7 = -0.2129999995232f;
        p.cc.colorCorrection8 = 0.6850000023842f;
        p.cc.colorCorrection9 = 0.930999994278f;
        p.cc.colorCorrection10 = -0.5540000200272f;
        p.cc.colorCorrection11 = -0.5540000200272f;
        p.cc.colorCorrection12 = 0.04600000008941f;
        p.depth_table.depthClampMax = 65536;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityShift = 0;
        p.ae.meanIntensitySetPoint = 400;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
        p.depth_exposure.exposure = 33000.f;
        p.depth_auto_exposure.auto_exposure = 1;
        p.depth_gain.gain = 16.f;
    }


    void default_405(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 500;
        p.depth_controls.deepSeaNeighborThreshold = 7;
        p.depth_controls.deepSeaSecondPeakThreshold = 325;
        p.depth_controls.lrAgreeThreshold = 24;
        p.depth_controls.minusDecrement = 10;
        p.depth_controls.plusIncrement = 10;
        p.depth_controls.scoreThreshA = 1;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 4.f;
        p.rsm.removeThresh = 63;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 3;
        p.rsvc.minSouth = 1;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 51;
        p.rctc.rauDiffThresholdRed = 51;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 60;
        p.spc.sloK1PenaltyMod1 = 105;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 190;
        p.spc.sloK2PenaltyMod2 = 130;
        p.hdad.lambdaAD = 800.f;
        p.hdad.lambdaCensus = 26.f;
        p.cc.colorCorrection1 = 0.4620000123978f;
        p.cc.colorCorrection2 = 0.5400000214577f;
        p.cc.colorCorrection3 = 0.5400000214577f;
        p.cc.colorCorrection4 = 0.2080000042915f;
        p.cc.colorCorrection5 = -0.3319999873638f;
        p.cc.colorCorrection6 = -0.2129999995232f;
        p.cc.colorCorrection7 = -0.2129999995232f;
        p.cc.colorCorrection8 = 0.6850000023842f;
        p.cc.colorCorrection9 = 0.930999994278f;
        p.cc.colorCorrection10 = -0.5540000200272f;
        p.cc.colorCorrection11 = -0.5540000200272f;
        p.cc.colorCorrection12 = 0.04600000008941f;
        p.depth_table.depthClampMax = 65536;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityShift = 0;
        p.ae.meanIntensitySetPoint = 400;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
        p.laser_state.laser_state = 1;
        p.laser_power.laser_power = 150.f;
        p.depth_exposure.exposure = 33000.f;
        p.depth_auto_exposure.auto_exposure = 1;
        p.depth_gain.gain = 16.f;
    }


    void default_410(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 500;
        p.depth_controls.deepSeaNeighborThreshold = 7;
        p.depth_controls.deepSeaSecondPeakThreshold = 325;
        p.depth_controls.lrAgreeThreshold = 24;
        p.depth_controls.minusDecrement = 10;
        p.depth_controls.plusIncrement = 10;
        p.depth_controls.scoreThreshA = 1;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 4.f;
        p.rsm.removeThresh = 63;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 3;
        p.rsvc.minSouth = 1;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 51;
        p.rctc.rauDiffThresholdRed = 51;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 60;
        p.spc.sloK1PenaltyMod1 = 105;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 190;
        p.spc.sloK2PenaltyMod2 = 130;
        p.hdad.lambdaAD = 800.f;
        p.hdad.lambdaCensus = 26.f;
        p.cc.colorCorrection1 = 0.4620000123978f;
        p.cc.colorCorrection2 = 0.5400000214577f;
        p.cc.colorCorrection3 = 0.5400000214577f;
        p.cc.colorCorrection4 = 0.2080000042915f;
        p.cc.colorCorrection5 = -0.3319999873638f;
        p.cc.colorCorrection6 = -0.2129999995232f;
        p.cc.colorCorrection7 = -0.2129999995232f;
        p.cc.colorCorrection8 = 0.6850000023842f;
        p.cc.colorCorrection9 = 0.930999994278f;
        p.cc.colorCorrection10 = -0.5540000200272f;
        p.cc.colorCorrection11 = -0.5540000200272f;
        p.cc.colorCorrection12 = 0.04600000008941f;
        p.depth_table.depthClampMax = 65536;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityShift = 0;
        p.ae.meanIntensitySetPoint = 400;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
        p.laser_state.laser_state = 1;
        p.laser_power.laser_power = 150.f;
        p.depth_exposure.exposure = 33000.f;
        p.depth_auto_exposure.auto_exposure = 1;
        p.depth_gain.gain = 16.f;
    }


    void default_420(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 500;
        p.depth_controls.deepSeaNeighborThreshold = 7;
        p.depth_controls.deepSeaSecondPeakThreshold = 325;
        p.depth_controls.lrAgreeThreshold = 24;
        p.depth_controls.minusDecrement = 10;
        p.depth_controls.plusIncrement = 10;
        p.depth_controls.scoreThreshA = 1;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 4.f;
        p.rsm.removeThresh = 63;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 3;
        p.rsvc.minSouth = 1;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 51;
        p.rctc.rauDiffThresholdRed = 51;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 60;
        p.spc.sloK1PenaltyMod1 = 105;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 190;
        p.spc.sloK2PenaltyMod2 = 130;
        p.hdad.lambdaAD = 800.f;
        p.hdad.lambdaCensus = 26.f;
        p.cc.colorCorrection1 = 0.2989999949932f;
        p.cc.colorCorrection2 = 0.2939999997616f;
        p.cc.colorCorrection3 = 0.2939999997616f;
        p.cc.colorCorrection4 = 0.1140000000596f;
        p.cc.colorCorrection5 = 0.f;
        p.cc.colorCorrection6 = 0.f;
        p.cc.colorCorrection7 = 0.f;
        p.cc.colorCorrection8 = 0.f;
        p.cc.colorCorrection9 = 0.f;
        p.cc.colorCorrection10 = 0.f;
        p.cc.colorCorrection11 = 0.f;
        p.cc.colorCorrection12 = 0.f;
        p.depth_table.depthClampMax = 65536;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityShift = 0;
        p.ae.meanIntensitySetPoint = 1536;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
        p.depth_exposure.exposure = 8500.f;
        p.depth_auto_exposure.auto_exposure = 1;
        p.depth_gain.gain = 16.f;
    }


    void default_430(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 500;
        p.depth_controls.deepSeaNeighborThreshold = 7;
        p.depth_controls.deepSeaSecondPeakThreshold = 325;
        p.depth_controls.lrAgreeThreshold = 24;
        p.depth_controls.minusDecrement = 10;
        p.depth_controls.plusIncrement = 10;
        p.depth_controls.scoreThreshA = 1;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 4.f;
        p.rsm.removeThresh = 63;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 3;
        p.rsvc.minSouth = 1;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 51;
        p.rctc.rauDiffThresholdRed = 51;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 60;
        p.spc.sloK1PenaltyMod1 = 105;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 190;
        p.spc.sloK2PenaltyMod2 = 130;
        p.hdad.lambdaAD = 800.f;
        p.hdad.lambdaCensus = 26.f;
        p.cc.colorCorrection1 = 0.2989999949932f;
        p.cc.colorCorrection2 = 0.2939999997616f;
        p.cc.colorCorrection3 = 0.2939999997616f;
        p.cc.colorCorrection4 = 0.1140000000596f;
        p.cc.colorCorrection5 = 0.f;
        p.cc.colorCorrection6 = 0.f;
        p.cc.colorCorrection7 = 0.f;
        p.cc.colorCorrection8 = 0.f;
        p.cc.colorCorrection9 = 0.f;
        p.cc.colorCorrection10 = 0.f;
        p.cc.colorCorrection11 = 0.f;
        p.cc.colorCorrection12 = 0.f;
        p.depth_table.depthClampMax = 65536;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityShift = 0;
        p.ae.meanIntensitySetPoint = 1536;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
        p.laser_state.laser_state = 1;
        p.laser_power.laser_power = 150.f;
        p.depth_exposure.exposure = 8500.f;
        p.depth_auto_exposure.auto_exposure = 1;
        p.depth_gain.gain = 16.f;
    }

    void high_res_high_accuracy(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 796;
        p.depth_controls.deepSeaNeighborThreshold = 108;
        p.depth_controls.deepSeaSecondPeakThreshold = 647;
        p.depth_controls.lrAgreeThreshold = 10;
        p.depth_controls.minusDecrement = 25;
        p.depth_controls.plusIncrement = 2;
        p.depth_controls.scoreThreshA = 4;
        p.depth_controls.scoreThreshB = 2893;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 1722;
        p.rsm.diffThresh = 1.660570025444f;
        p.rsm.removeThresh = 136;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.7269909977913f;
        p.rsvc.minEast = 6;
        p.rsvc.minNorth = 3;
        p.rsvc.minNSsum = 7;
        p.rsvc.minSouth = 2;
        p.rsvc.minWest = 2;
        p.rsvc.minWEsum = 12;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 0;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 1;
        p.rctc.rauDiffThresholdBlue = 803;
        p.rctc.rauDiffThresholdGreen = 578;
        p.rctc.rauDiffThresholdRed = 1007;
        p.sctc.diffThresholdBlue = 13;
        p.sctc.diffThresholdGreen = 15;
        p.sctc.diffThresholdRed = 30;
        p.spc.sloK1Penalty = 155;
        p.spc.sloK1PenaltyMod1 = 160;
        p.spc.sloK1PenaltyMod2 = 59;
        p.spc.sloK2Penalty = 190;
        p.spc.sloK2PenaltyMod1 = 507;
        p.spc.sloK2PenaltyMod2 = 493;
        p.hdad.lambdaAD = 751.f;
        p.hdad.lambdaCensus = 6.f;
    }

    void high_res_high_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 789;
        p.depth_controls.deepSeaNeighborThreshold = 12;
        p.depth_controls.deepSeaSecondPeakThreshold = 222;
        p.depth_controls.lrAgreeThreshold = 18;
        p.depth_controls.minusDecrement = 6;
        p.depth_controls.plusIncrement = 21;
        p.depth_controls.scoreThreshA = 96;
        p.depth_controls.scoreThreshB = 1443;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 2466;
        p.rsm.diffThresh = 1.228299975395f;
        p.rsm.removeThresh = 82;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.2664879858494f;
        p.rsvc.minEast = 2;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 6;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 3;
        p.rsvc.minWEsum = 7;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 0;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 112;
        p.rctc.rauDiffThresholdGreen = 585;
        p.rctc.rauDiffThresholdRed = 18;
        p.sctc.diffThresholdBlue = 8;
        p.sctc.diffThresholdGreen = 200;
        p.sctc.diffThresholdRed = 279;
        p.spc.sloK1Penalty = 55;
        p.spc.sloK1PenaltyMod1 = 326;
        p.spc.sloK1PenaltyMod2 = 134;
        p.spc.sloK2Penalty = 235;
        p.spc.sloK2PenaltyMod1 = 506;
        p.spc.sloK2PenaltyMod2 = 206;
        p.hdad.lambdaAD = 618.f;
        p.hdad.lambdaCensus = 15.f;
    }

    void high_res_mid_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 1021;
        p.depth_controls.deepSeaNeighborThreshold = 97;
        p.depth_controls.deepSeaSecondPeakThreshold = 600;
        p.depth_controls.lrAgreeThreshold = 19;
        p.depth_controls.minusDecrement = 23;
        p.depth_controls.plusIncrement = 3;
        p.depth_controls.scoreThreshA = 54;
        p.depth_controls.scoreThreshB = 887;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 1.816750049591f;
        p.rsm.removeThresh = 81;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 3;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 6;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 5;
        p.rsvc.minWEsum = 11;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 1;
        p.rctc.rauDiffThresholdBlue = 14;
        p.rctc.rauDiffThresholdGreen = 723;
        p.rctc.rauDiffThresholdRed = 186;
        p.sctc.diffThresholdBlue = 16;
        p.sctc.diffThresholdGreen = 259;
        p.sctc.diffThresholdRed = 896;
        p.spc.sloK1Penalty = 132;
        p.spc.sloK1PenaltyMod1 = 77;
        p.spc.sloK1PenaltyMod2 = 234;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 390;
        p.spc.sloK2PenaltyMod2 = 151;
        p.hdad.lambdaAD = 935.f;
        p.hdad.lambdaCensus = 26.f;
    }

    void low_res_high_accuracy(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 871;
        p.depth_controls.deepSeaNeighborThreshold = 113;
        p.depth_controls.deepSeaSecondPeakThreshold = 310;
        p.depth_controls.lrAgreeThreshold = 28;
        p.depth_controls.minusDecrement = 1;
        p.depth_controls.plusIncrement = 1;
        p.depth_controls.scoreThreshA = 70;
        p.depth_controls.scoreThreshB = 1890;
        p.depth_controls.textureCountThreshold = 8;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 5.206029891968f;
        p.rsm.removeThresh = 86;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.7110940217972f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 5;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 7;
        p.rsvc.minWEsum = 7;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 0;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 23;
        p.rctc.rauDiffThresholdGreen = 297;
        p.rctc.rauDiffThresholdRed = 95;
        p.sctc.diffThresholdBlue = 72;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 72;
        p.spc.sloK1Penalty = 176;
        p.spc.sloK1PenaltyMod1 = 196;
        p.spc.sloK1PenaltyMod2 = 36;
        p.spc.sloK2Penalty = 414;
        p.spc.sloK2PenaltyMod1 = 96;
        p.spc.sloK2PenaltyMod2 = 57;
        p.hdad.lambdaAD = 74.f;
        p.hdad.lambdaCensus = 26.f;
        p.census.uDiameter = 8;
        p.census.vDiameter = 9;
    }

    void low_res_high_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 973;
        p.depth_controls.deepSeaNeighborThreshold = 91;
        p.depth_controls.deepSeaSecondPeakThreshold = 463;
        p.depth_controls.lrAgreeThreshold = 20;
        p.depth_controls.minusDecrement = 2;
        p.depth_controls.plusIncrement = 18;
        p.depth_controls.scoreThreshA = 90;
        p.depth_controls.scoreThreshB = 3440;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 3639;
        p.rsm.diffThresh = 5.890840053558f;
        p.rsm.removeThresh = 68;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.421687990427f;
        p.rsvc.minEast = 1;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 5;
        p.rsvc.minSouth = 2;
        p.rsvc.minWest = 6;
        p.rsvc.minWEsum = 4;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 1;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 300;
        p.rctc.rauDiffThresholdGreen = 12;
        p.rctc.rauDiffThresholdRed = 60;
        p.sctc.diffThresholdBlue = 105;
        p.sctc.diffThresholdGreen = 60;
        p.sctc.diffThresholdRed = 64;
        p.spc.sloK1Penalty = 170;
        p.spc.sloK1PenaltyMod1 = 67;
        p.spc.sloK1PenaltyMod2 = 59;
        p.spc.sloK2Penalty = 386;
        p.spc.sloK2PenaltyMod1 = 86;
        p.spc.sloK2PenaltyMod2 = 60;
        p.hdad.lambdaAD = 686.f;
        p.hdad.lambdaCensus = 26.f;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
    }

    void low_res_mid_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 696;
        p.depth_controls.deepSeaNeighborThreshold = 43;
        p.depth_controls.deepSeaSecondPeakThreshold = 476;
        p.depth_controls.lrAgreeThreshold = 30;
        p.depth_controls.minusDecrement = 9;
        p.depth_controls.plusIncrement = 16;
        p.depth_controls.scoreThreshA = 43;
        p.depth_controls.scoreThreshB = 1885;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 2817;
        p.rsm.diffThresh = 6.447229862213f;
        p.rsm.removeThresh = 95;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.2744660079479f;
        p.rsvc.minEast = 6;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 2;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 7;
        p.rsvc.minWEsum = 7;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 51;
        p.rctc.rauDiffThresholdGreen = 31;
        p.rctc.rauDiffThresholdRed = 424;
        p.sctc.diffThresholdBlue = 69;
        p.sctc.diffThresholdGreen = 72;
        p.sctc.diffThresholdRed = 124;
        p.spc.sloK1Penalty = 117;
        p.spc.sloK1PenaltyMod1 = 33;
        p.spc.sloK1PenaltyMod2 = 64;
        p.spc.sloK2Penalty = 410;
        p.spc.sloK2PenaltyMod1 = 80;
        p.spc.sloK2PenaltyMod2 = 74;
        p.hdad.lambdaAD = 183.f;
        p.hdad.lambdaCensus = 26.f;
        p.census.uDiameter = 9;
        p.census.vDiameter = 9;
    }

    void mid_res_high_accuracy(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 347;
        p.depth_controls.deepSeaNeighborThreshold = 82;
        p.depth_controls.deepSeaSecondPeakThreshold = 205;
        p.depth_controls.lrAgreeThreshold = 18;
        p.depth_controls.minusDecrement = 15;
        p.depth_controls.plusIncrement = 5;
        p.depth_controls.scoreThreshA = 80;
        p.depth_controls.scoreThreshB = 2047;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 3474;
        p.rsm.diffThresh = 3.329339981079f;
        p.rsm.removeThresh = 112;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.9618660211563f;
        p.rsvc.minEast = 3;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 6;
        p.rsvc.minSouth = 2;
        p.rsvc.minWest = 2;
        p.rsvc.minWEsum = 3;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 26;
        p.rctc.rauDiffThresholdGreen = 975;
        p.rctc.rauDiffThresholdRed = 29;
        p.sctc.diffThresholdBlue = 442;
        p.sctc.diffThresholdGreen = 16;
        p.sctc.diffThresholdRed = 770;
        p.spc.sloK1Penalty = 21;
        p.spc.sloK1PenaltyMod1 = 3;
        p.spc.sloK1PenaltyMod2 = 27;
        p.spc.sloK2Penalty = 182;
        p.spc.sloK2PenaltyMod1 = 41;
        p.spc.sloK2PenaltyMod2 = 63;
        p.hdad.lambdaAD = 630.f;
        p.hdad.lambdaCensus = 26.f;
        p.census.uDiameter = 6;
        p.census.vDiameter = 7;
    }

    void mid_res_high_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 276;
        p.depth_controls.deepSeaNeighborThreshold = 4;
        p.depth_controls.deepSeaSecondPeakThreshold = 6;
        p.depth_controls.lrAgreeThreshold = 32;
        p.depth_controls.minusDecrement = 1;
        p.depth_controls.plusIncrement = 4;
        p.depth_controls.scoreThreshA = 68;
        p.depth_controls.scoreThreshB = 1949;
        p.depth_controls.textureCountThreshold = 1;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 5.069789886475f;
        p.rsm.removeThresh = 75;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 7;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 6;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 6;
        p.rsvc.minWEsum = 14;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 1;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 11;
        p.rctc.rauDiffThresholdGreen = 660;
        p.rctc.rauDiffThresholdRed = 17;
        p.sctc.diffThresholdBlue = 4;
        p.sctc.diffThresholdGreen = 542;
        p.sctc.diffThresholdRed = 982;
        p.spc.sloK1Penalty = 479;
        p.spc.sloK1PenaltyMod1 = 4;
        p.spc.sloK1PenaltyMod2 = 25;
        p.spc.sloK2Penalty = 342;
        p.spc.sloK2PenaltyMod1 = 69;
        p.spc.sloK2PenaltyMod2 = 225;
        p.hdad.lambdaAD = 850.f;
        p.hdad.lambdaCensus = 19.f;
        p.census.uDiameter = 9;
        p.census.vDiameter = 3;
    }

    void mid_res_mid_density(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 175;
        p.depth_controls.deepSeaNeighborThreshold = 1;
        p.depth_controls.deepSeaSecondPeakThreshold = 3;
        p.depth_controls.lrAgreeThreshold = 32;
        p.depth_controls.minusDecrement = 14;
        p.depth_controls.plusIncrement = 22;
        p.depth_controls.scoreThreshA = 3;
        p.depth_controls.scoreThreshB = 972;
        p.depth_controls.textureCountThreshold = 6;
        p.depth_controls.textureDifferenceThreshold = 0;
        p.rsm.diffThresh = 5.859620094299f;
        p.rsm.removeThresh = 70;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 1.f;
        p.rsvc.minEast = 3;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 6;
        p.rsvc.minSouth = 2;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 5;
        p.rsvc.uShrink = 4;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 1;
        p.color_control.disableSLORightColor = 0;
        p.rctc.rauDiffThresholdBlue = 692;
        p.rctc.rauDiffThresholdGreen = 12;
        p.rctc.rauDiffThresholdRed = 80;
        p.sctc.diffThresholdBlue = 18;
        p.sctc.diffThresholdGreen = 493;
        p.sctc.diffThresholdRed = 390;
        p.spc.sloK1Penalty = 134;
        p.spc.sloK1PenaltyMod1 = 10;
        p.spc.sloK1PenaltyMod2 = 70;
        p.spc.sloK2Penalty = 397;
        p.spc.sloK2PenaltyMod1 = 21;
        p.spc.sloK2PenaltyMod2 = 226;
        p.hdad.lambdaAD = 978.f;
        p.hdad.lambdaCensus = 21.f;
        p.census.uDiameter = 8;
        p.census.vDiameter = 5;
    }

    void hand_gesture(preset& p)
    {
        p.depth_controls.deepSeaMedianThreshold = 240;
        p.depth_controls.deepSeaNeighborThreshold = 110;
        p.depth_controls.deepSeaSecondPeakThreshold = 31;
        p.depth_controls.lrAgreeThreshold = 20;
        p.depth_controls.minusDecrement = 20;
        p.depth_controls.plusIncrement = 3;
        p.depth_controls.scoreThreshA = 24;
        p.depth_controls.scoreThreshB = 791;
        p.depth_controls.textureCountThreshold = 0;
        p.depth_controls.textureDifferenceThreshold = 783;
        p.rsm.diffThresh = 3.8125f;
        p.rsm.removeThresh = 92;
        p.rsm.rsmBypass = 0;
        p.rsm.sloRauDiffThresh = 0.46875f;
        p.rsvc.minEast = 3;
        p.rsvc.minNorth = 1;
        p.rsvc.minNSsum = 4;
        p.rsvc.minSouth = 3;
        p.rsvc.minWest = 1;
        p.rsvc.minWEsum = 14;
        p.rsvc.uShrink = 3;
        p.rsvc.vShrink = 1;
        p.color_control.disableRAUColor = 0;
        p.color_control.disableSADColor = 0;
        p.color_control.disableSADNormalize = 0;
        p.color_control.disableSLOLeftColor = 0;
        p.color_control.disableSLORightColor = 1;
        p.rctc.rauDiffThresholdBlue = 50;
        p.rctc.rauDiffThresholdGreen = 73;
        p.rctc.rauDiffThresholdRed = 141;
        p.sctc.diffThresholdBlue = 130;
        p.sctc.diffThresholdGreen = 244;
        p.sctc.diffThresholdRed = 618;
        p.spc.sloK1Penalty = 63;
        p.spc.sloK1PenaltyMod1 = 14;
        p.spc.sloK1PenaltyMod2 = 119;
        p.spc.sloK2Penalty = 45;
        p.spc.sloK2PenaltyMod1 = 21;
        p.spc.sloK2PenaltyMod2 = 12;
        p.hdad.ignoreSAD = 0;
        p.hdad.lambdaAD = 1001.f;
        p.hdad.lambdaCensus = 7.f;
        p.depth_table.depthClampMax = 65535;
        p.depth_table.depthClampMin = 0;
        p.depth_table.depthUnits = 1000;
        p.depth_table.disparityMode = 0;
        p.depth_table.disparityShift = 0;
        p.census.uDiameter = 9;
        p.census.vDiameter = 3;
    }

    void d415_remove_ir(preset& p)
    {
        p.cc.colorCorrection1 = 0.5205079913139f;
        p.cc.colorCorrection2 = 1.990234017372f;
        p.cc.colorCorrection3 = 1.506836056709f;
        p.cc.colorCorrection4 = -2.f;
        p.cc.colorCorrection5 = -2.f;
        p.cc.colorCorrection6 = -0.08203099668026f;
        p.cc.colorCorrection7 = 1.123046994209f;
        p.cc.colorCorrection8 = 1.013671994209f;
        p.cc.colorCorrection9 = 1.698241949081f;
        p.cc.colorCorrection10 = -2.f;
        p.cc.colorCorrection11 = 0.5751950144768f;
        p.cc.colorCorrection12 = -0.4111329913139f;
    }

    void d460_remove_ir(preset& p)
    {
        p.cc.colorCorrection1 = 1.917968988419f;
        p.cc.colorCorrection2 = 1.990234017372f;
        p.cc.colorCorrection3 = -2.f;
        p.cc.colorCorrection4 = -2.f;
        p.cc.colorCorrection5 = -1.041015982628f;
        p.cc.colorCorrection6 = 0.0546870008111f;
        p.cc.colorCorrection7 = -0.21875f;
        p.cc.colorCorrection8 = 0.9042969942093f;
        p.cc.colorCorrection9 = 0.9042969942093f;
        p.cc.colorCorrection10 = -0.5478519797325f;
        p.cc.colorCorrection11 = -0.1367190033197f;
        p.cc.colorCorrection12 = -0.1914059966803f;
    }
}
