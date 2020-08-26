#pragma once
#include <PathTracingCPU/Core.hpp>
#include <functional>
#include <map>

namespace Alice::PathTracingCPU
{
    class AliceObject 
    {
    public:
        enum class EClassType 
        {
            EScene = 0,
            EMesh,
            EBSDF,
            EPhaseFunction,
            EEmitter,
            EMedium,
            ECamera,
            EIntegrator,
            ESampler,
            ETest,
            EReconstructionFilter,
            EClassTypeCount
        };

        virtual ~AliceObject() { }

        virtual EClassType GetClassType() const = 0;
        
        // 为当前对象添加一个子对象
        virtual void AddChild(Ref<AliceObject> child);

        // 设置父对象
        virtual void SetParent(Ref<AliceObject> parent);

        // 对象激活
        virtual void Activate();

        // 输出字符串 
        virtual std::string toString() const = 0;

        static std::string classTypeName(EClassType type) 
        {
            switch (type) {
            case EClassType::EScene:  return "scene";
            case EClassType::EMesh:  return "mesh";
            case EClassType::EBSDF:  return "bsdf";
            case EClassType::EEmitter: return "emitter";
            case EClassType::ECamera: return "camera";
            case EClassType::EIntegrator: return "integrator";
            case EClassType::ESampler: return "sampler";
            case EClassType::ETest: return "test";
            default:  return "<unknown>";
            }
        }
    };

    class PropertyList;
    class AliceObjectFactory 
    {
    public:
        typedef std::function<Ref<AliceObject>(const PropertyList&)> Constructor;

        static void RegisterClass(const std::string& name, const Constructor& constr);

        /**
         * \brief Construct an instance from the class of the given name
         *
         * \param name
         *     An internal name that is associated with this class. This is the
         *     'type' field found in the scene description XML files
         *
         * \param propList
         *     A list of properties that will be passed to the constructor
         *     of the class.
         */
        static Ref<AliceObject> CreateInstance(const std::string& name,const PropertyList& propList)
        {
            if (!m_constructors || m_constructors->find(name) == m_constructors->end())
                throw ALICE_ERROR_IO("A constructor for class \"%s\" could not be found!", name);
            return (*m_constructors)[name](propList);
        }
    private:
        static std::map<std::string, Constructor>* m_constructors;
    };
}