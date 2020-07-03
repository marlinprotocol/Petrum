#pragma once

#include <string>
#include <string_view>
#include "tscpp/api/TransformationPlugin.h"

namespace atscppapi
{
namespace transformations
{
  /**
   * Internal state for Deflate Transformations
   * @private
   */
  struct GzipDeflateTransformationState;

  /**
   * @brief A TransformationPlugin to easily add gzip deflate to your TransformationPlugin chain.
   *
   * The GzipDeflateTransformation is a helper transformation that can be used
   * to easily compress content. For a full example of GzipDeflateTransformation
   * and GzipInflateTransformation see examples/gzip_transformation/.
   *
   * @note GzipDeflateTransformation DOES NOT set Content-Encoding headers, it is the
   * users responsibility to set any applicable headers.
   *
   * @see GzipInflateTransformation
   */
  class GzipDeflateTransformation : public TransformationPlugin
  {
  public:
    /**
     * A full example of how to use GzipDeflateTransformation and GzipInflateTransformation is available
     * in examples/gzip_tranformation/
     *
     * @param transaction As with any TransformationPlugin you must pass in the transaction
     * @param type because the GzipDeflateTransformation can be used with both requests and responses
     *  you must specify the Type.
     *
     * @see TransformationPlugin::Type
     */
    GzipDeflateTransformation(Transaction &transaction, TransformationPlugin::Type type);

    /**
     * Any TransformationPlugin must implement consume(), this method will take content
     * from the transformation chain and gzip compress it.
     *
     * @param data the input data to compress
     */
    void consume(std::string_view data) override;

    /**
     * Any TransformationPlugin must implement handleInputComplete(), this method will
     * finalize the gzip compression and flush any remaining data and the epilouge.
     */
    void handleInputComplete() override;

    ~GzipDeflateTransformation() override;

  private:
    GzipDeflateTransformationState *state_; /** Internal state for Gzip Deflate Transformations */
  };
} // namespace transformations
} // namespace atscppapi
