#ifndef VALUE_H
#define VALUE_H

#include <QString>

#include "input.h"

class NodeValue
{
public:
  NodeValue(const NodeParam::DataType& type, const QVariant& data, const QString& tag = QString());

  const NodeParam::DataType& type() const;
  const QVariant& data() const;
  const QString& tag() const;

private:
  NodeParam::DataType type_;
  QVariant data_;
  QString tag_;

};

class NodeValueTable
{
public:
  NodeValueTable();

  QVariant Get(const NodeParam::DataType& type, const QString& tag = QString());
  QVariant Take(const NodeParam::DataType& type, const QString& tag = QString());
  void Push(const NodeValue& value);
  void Push(const NodeParam::DataType& type, const QVariant& data, const QString& tag = QString());
  void Prepend(const NodeValue& value);
  void Prepend(const NodeParam::DataType& type, const QVariant& data, const QString& tag = QString());
  const NodeValue& At(int index) const;
  int Count() const;

  bool isEmpty() const;

private:
  QVariant GetInternal(const NodeParam::DataType& type, const QString& tag, bool remove);

  QList<NodeValue> values_;

};

class NodeValueDatabase
{
public:
  NodeValueDatabase();

  NodeValueTable operator[](const QString& input_id) const;
  NodeValueTable operator[](const NodeInput* input) const;

  void Insert(const QString& key, const NodeValueTable &value);
  void Insert(const NodeInput* key, const NodeValueTable& value);

  NodeValueTable Merge() const;

private:
  QHash<QString, NodeValueTable> tables_;

};

#endif // VALUE_H