#pragma once

#include "utils/string.h"

namespace dank {

	class RTTI {

	public:
		virtual const size_t TypeIdInstance() const = 0;

		virtual RTTI* QueryInterface(const size_t) { return nullptr; }
		virtual const RTTI* QueryInterface(const size_t) const { return nullptr; }

		virtual bool Is(size_t id) const { return false; }
		virtual bool Is(const String& name) const { return false; }

		template <typename T>
		T* As() {
			if (Is(T::TypeIdClass())) { 
				return (T*)this; 
			} 
			return nullptr; 
		}
		
		template <typename T>
		const T* As() const {
			if (Is(T::TypeIdClass())) {
				return (T*)this;
			}
			return nullptr;
		}
	};

#define RTTI_IMPLEMENTATION(Type, ParentType)							\
	public:																\
        static String TypeName() { return String(#Type); }				\
        virtual const size_t TypeIdInstance() const						\
        { return Type::TypeIdClass(); }									\
        static const size_t TypeIdClass()								\
        { static int d = 0; return (size_t) &d; }						\
        virtual dank::RTTI* QueryInterface( const size_t id )			\
        {																\
            if (id == TypeIdClass())									\
                { return (RTTI*)this; }									\
            else														\
                { return ParentType::QueryInterface(id); }				\
        }																\
        virtual const dank::RTTI* QueryInterface( const size_t id ) const \
        {																\
            if (id == TypeIdClass())									\
                { return (RTTI*)this; }									\
            else														\
                { return ParentType::QueryInterface(id); }				\
        }																\
        virtual bool Is(const size_t id) const							\
        {																\
            if (id == TypeIdClass())									\
                { return true; }										\
            else														\
                { return ParentType::Is(id); }							\
        }																\
        virtual bool Is(const String& name) const						\
        {																\
            if (name == TypeName())										\
                { return true; }										\
            else														\
                { return ParentType::Is(name); }						\
        } 
}
