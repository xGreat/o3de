/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Atom/RHI.Edit/ShaderPlatformInterface.h>

namespace AZ
{
    namespace DX12
    {
        class ShaderPlatformInterface : 
            public RHI::ShaderPlatformInterface
        {
        public:
            explicit ShaderPlatformInterface(uint32_t apiUniqueIndex);

            RHI::APIType GetAPIType() const override;
            AZ::Name GetAPIName() const override;

            RHI::Ptr<RHI::ShaderStageFunction> CreateShaderStageFunction(
                const StageDescriptor& stageDescriptor) override;

            bool IsShaderStageForRaster(RHI::ShaderHardwareStage shaderStageType) const override;
            bool IsShaderStageForCompute(RHI::ShaderHardwareStage shaderStageType) const override;
            bool IsShaderStageForRayTracing(RHI::ShaderHardwareStage shaderStageType) const override;

            RHI::Ptr<RHI::PipelineLayoutDescriptor> CreatePipelineLayoutDescriptor() override;

            bool BuildPipelineLayoutDescriptor(
                RHI::Ptr<RHI::PipelineLayoutDescriptor> pipelineLayoutDescriptor,
                const ShaderResourceGroupInfoList& srgInfoList,
                const RootConstantsInfo& rootConstantsInfo,
                const RHI::ShaderBuildArguments& shaderBuildArguments) override;

            bool CompilePlatformInternal(
                const AssetBuilderSDK::PlatformInfo& platform,
                const AZStd::string& shaderSourcePath,
                const AZStd::string& functionName,
                RHI::ShaderHardwareStage shaderStage,
                const AZStd::string& tempFolderPath,
                StageDescriptor& outputDescriptor,
                const RHI::ShaderBuildArguments& shaderBuildArguments,
                const bool useSpecializationConstants) const override;

            const char* GetAzslHeader(const AssetBuilderSDK::PlatformInfo& platform) const override;

        private:
            ShaderPlatformInterface() = delete;

            bool CompileHLSLShader(
                const AZStd::string& shaderSourceFile,
                const AZStd::string& tempFolder,
                const AZStd::string& entryPoint,
                const RHI::ShaderHardwareStage shaderStageType,
                const RHI::ShaderBuildArguments& shaderBuildArguments,
                AZStd::vector<uint8_t>& m_byteCode,
                ByProducts& products,
                AZStd::string& specializationOffsetsFile,
                const bool useSpecializationConstants) const;

            const Name m_apiName;
        };
    }
}
