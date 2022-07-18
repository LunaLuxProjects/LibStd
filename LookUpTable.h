#pragma once
#include <assert.h>
#include <initializer_list>
#include <lstd/DataType.h>
#include <lstd/Intrinsics.h>
namespace lstd
{
template<typename Key, typename Value> struct ReadOnlyLookupTable
{
  private:
    struct LookUpTable
    {
      Key key;
      Value value;
      LookUpTable() noexcept = default;
      LookUpTable(const Key key, const Value value) noexcept : key(key), value(value) {}

      bool operator==(const Key& key) const noexcept { return this->key == key;};
    }* table;
    data_size size_of_table = 0;
  public:
    ReadOnlyLookupTable() noexcept = default;
    ReadOnlyLookupTable(std::initializer_list<LookUpTable> entries) noexcept 
    {
      table = new LookUpTable[(size_of_table = entries.size())];
      data_size index = 0;
      for(auto& entry : entries)
        table[index++] = entry;
    }
    ~ReadOnlyLookupTable() noexcept = default;

    const Value &find(const Key & key) const noexcept
    {
      for(data_size i = 0; i < size_of_table; i++)
      {
        if(table[i] == key) return table[i].value;
      }
      assert(true);
      return table[0].value;
    }
};
} // namespace lstd