#ifndef EXPRESSIONMATRIX_H
#define EXPRESSIONMATRIX_H
#include <ace/core/AceCore.h>



class ExpressionMatrix : public QAbstractTableModel, public EAbstractData
{
   Q_OBJECT
public:
   using Expression = float;
   enum class Transform
   {
      None
      ,NLog
      ,Log2
      ,Log10
   };
   class Gene
   {
   public:
      Gene(ExpressionMatrix* matrix):
         _expressions(new Expression[matrix->_sampleSize]),
         _matrix(matrix)
         {}
      Gene(const Gene&) = delete;
      ~Gene() { delete _expressions; }
      void readGene(int index) const;
      void writeGene(int index);
      Expression& at(int index);
      const Expression& at(int index) const;
      Expression& operator[](int index) { return _expressions[index]; }
   private:
      Expression* _expressions;
      ExpressionMatrix* _matrix;
   };
   virtual void readData() override final;
   virtual quint64 getDataEnd() const override final;
   virtual void newData() override final;
   virtual void prepare(bool preAllocate) override final;
   virtual void finish() override final;
   virtual QAbstractTableModel* getModel() override final { return this; }
   void initialize(QStringList geneNames, QStringList sampleNames);
   void setTransform(Transform scale);
   qint32 getGeneSize() const { return _geneSize; }
   qint32 getSampleSize() const { return _sampleSize; }
   qint64 getRawSize() const;
   Expression* dumpRawData() const;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const;
   int rowCount(const QModelIndex& parent) const override final;
   int columnCount(const QModelIndex& parent) const override final;
   QVariant data(const QModelIndex& index, int role) const override final;
private:
   void readGene(int index, Expression* _expressions) const;
   void writeGene(int index, const Expression* _expressions);
   qint32 _geneSize {0};
   qint32 _sampleSize {0};
};



#endif
